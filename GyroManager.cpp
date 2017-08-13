/*
 * This file is part of XPilotView.
 *
 * XPilotView is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XPilotView is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XPilotView.  If not, see <http://www.gnu.org/licenses/>
 */

/* 
 * File:   GyroManager.cpp
 * Author: dave
 * 
 * Created on August 4, 2017, 8:58 PM
 */

#include <complex>

#include "GyroManager.hpp"
#include "XPilotViewUtils.hpp"


bool GyroManager::isRunning = false;
bool GyroManager::setCenterView = false;
unsigned int GyroManager::sfd;
json* GyroManager::gyroPrefs = NULL;
GyroAngles GyroManager::viewCenter(0.0, 0.0, 0.0);
GyroAnglesPtr GyroManager::angles = std::make_shared<GyroAngles>(0.0, 0.0, 0.0);

GyroManager::GyroManager()
{
}

GyroManager::~GyroManager()
{
    this->stop();
}

void GyroManager::start()
{
    try
    {
        this->isRunning = true;
        if (gyroPrefs == NULL) gyroPrefs = prefMgr.getPanel()->getPreferences();
        this->startManagerThread();

    } catch (const std::exception& ex)
    {
        std::string msg( std::string("XPilotView: GyroManager::start() : ") + ex.what());
        XPilotViewUtils::logMessage(msg);
    }
}

void GyroManager::stop()
{
    try
    {
        if (this->isRunning)
        {
            this->isRunning = false;
            sleep(1); // wait for thread loop to exit
            tcsetattr(sfd, TCSANOW, &savetty);
            close(sfd);
        }

    } catch (const std::exception& ex)
    {
        std::string msg( std::string("XPilotView: GyroManager::stop() : ") + ex.what());
        XPilotViewUtils::logMessage(msg);
    }
}

GyroAnglesPtr GyroManager::getAngles()
{
    return GyroManager::angles;
}

void GyroManager::showPreferences(bool show)
{
    prefMgr.showPanel(show);
}

void GyroManager::togglePreferencesPanel()
{
    prefMgr.togglePanel();
}

std::string GyroManager::getTTyPath()
{
    return prefMgr.getTTyPath();
}

void GyroManager::setViewCenter()
{
    setCenterView = true;
}

void *GyroManagerThread(void *arg)
{
    unsigned char buf[80];
    float a[3];
    AngleSet lastAngle = {0.0, 0.0, 0.0};
    json* prefs = PreferencesManager::prefPanel->getPreferences();

    try
    {
        while (GyroManager::isRunning)
        {
            int rdlen = read(GyroManager::sfd, buf, 1);

            if (rdlen > 0)
            {
                if (buf[0] == 0x55)
                {
                    rdlen = read(GyroManager::sfd, &buf[1], 10);
                    if (buf[1] == 0x53)
                    {
                        string slag = (*GyroManager::gyroPrefs)["filterLag"];
                        float lag = std::stof(slag);

                        string rscale = (*GyroManager::gyroPrefs)["rollScale"];
                        float rollScale = std::stof(rscale);
                        string pscale = (*GyroManager::gyroPrefs)["pitchScale"];
                        float pitchScale = std::stof(pscale);
                        string hscale = (*GyroManager::gyroPrefs)["headingScale"];
                        float headingScale = std::stof(hscale);
                        //std::cout << "hscale= " << hscalef << " vscale= " << vscalef << std::endl;

                        GyroManager::decode(buf, a);

                        // normalize to the range -90, +90
                        a[0] = GyroManager::normalizeAngle(a[0]);
                        a[1] = GyroManager::normalizeAngle(a[1]);
                        a[2] = GyroManager::normalizeAngle(a[2]);
                        //std::cout << "roll " << a[0] << " pitch " << a[1] << " yaw " << a[2] << std::endl;

                        // apply smoothing
                        float deltaA = a[0] - lastAngle.roll;
                        lastAngle.roll = lastAngle.roll + deltaA / lag;
                        deltaA = a[1] - lastAngle.pitch;
                        lastAngle.pitch = lastAngle.pitch + deltaA / lag;
                        deltaA = a[2] - lastAngle.heading;
                        lastAngle.heading = lastAngle.heading + deltaA / lag;

                        // center the view point
                        AngleSet center = GyroManager::viewCenter.getAngleSet();
                        float r = (lastAngle.roll - center.roll);
                        float p = (lastAngle.pitch - center.pitch);
                        float h = (lastAngle.heading - center.heading);

                        // Apply exponential acceleration to the view angle
                        // The formula is:
                        //
                        // viewangle = (headangle^x) / y
                        // 
                        // Given a curvature value of x, y can be calculated via:
                        //
                        //  y = 10^(1.3*x - 1.95))
                        //
                        //  This yields a curve such that a head deflection of
                        //  20 degrees yields a view deflection of 90 degrees.
                        //  Varing the value of x only changes the curvature of the
                        //  transform.
                        //

                        std::string sx = (*prefs)["headingScale"];
                        float x = stof(sx);
                        float e = 1.3 * x - 1.95;
                        float y = pow(10.0, e);
                        bool sign = signbit(h);
                        h = std::pow(abs(h), x) / y;
                        h = (sign ? h : -h);

                        sx = (*prefs)["pitchScale"];
                        x = stof(sx);
                        e = 1.3 * x - 1.95;
                        y = pow(10.0, e);
                        sign = signbit(p);
                        p = pow(abs(p), x) / y;
                        p = (sign ? -p : p);

                        sx = (*prefs)["rollScale"];
                        x = stof(sx);
                        e = 1.3 * x - 1.95;
                        y = pow(10.0, e);
                        sign = signbit(r);
                        r = pow(abs(r), x) / y;
                        r = (sign ? r : -r);

                        // angles object will be shared with and read by XPlugin loop
                        GyroManager::angles->setAngles(r, p, h);

                        // get new center values on command
                        if (GyroManager::setCenterView)
                        {
                            GyroManager::viewCenter.setAngles(a[0], a[1], a[2]);
                            GyroManager::setCenterView = false;
                        }
                    }
                }
            }
        }

    } catch (const std::exception& ex)
    {
        std::string msg( std::string("XPilotView: GyroManager::GyroManagerThread() : ") + ex.what());
        XPilotViewUtils::logMessage(msg);
    }
    GyroManager::isRunning = false;
}

float GyroManager::normalizeAngle(float a)
{
    float result = a;

    if (-180.0 < a && a < -90.0)
    {
        result = a + 180.0;
    } else if (90.0 < a && a < 180)
    {
        result = a - 180.0;
    }
    return result;
}

void GyroManager::startManagerThread()
{
    try
    {
        std::string ttypath = prefMgr.getTTyPath();
        sfd = this->opentty(ttypath);
        this->initGyro();

        pthread_t gmthread;
        int ret = 0;

        ret = pthread_create(&gmthread, NULL, &GyroManagerThread, NULL);

    } catch (const std::exception& ex)
    {
        std::string msg( std::string("XPilotView: GyroManager::startManagerThread() : ") + ex.what());
        XPilotViewUtils::logMessage(msg);
    }
}

unsigned int GyroManager::opentty(std::string ttypath)
{
    unsigned int sfd;
    speed_t spd = B115200;
    struct termios tty;
    int rc;

    try
    {
        sfd = open(ttypath.c_str(), O_RDWR | O_NOCTTY);

        rc = tcgetattr(sfd, &tty);
        if (rc < 0) sfd = -1;

        savetty = tty; /* preserve original settings for restoration */

        cfsetospeed(&tty, spd);
        cfsetispeed(&tty, spd);

        cfmakeraw(&tty);

        tty.c_cc[VMIN] = 1;
        tty.c_cc[VTIME] = 10;

        tty.c_cflag &= ~PARENB; // no parity bit
        tty.c_cflag &= ~CSTOPB; // one stop bit
        tty.c_cflag &= ~CRTSCTS; // no HW flow control
        tty.c_cflag |= CLOCAL | CREAD;
        rc = tcsetattr(sfd, TCSANOW, &tty);
        if (rc < 0) sfd = -3;

    } catch (const std::exception& ex)
    {
        std::string msg( std::string("XPilotView: GyroManager::opentty() : ") + ex.what());
        XPilotViewUtils::logMessage(msg);
    }

    return sfd;
}

void GyroManager::initGyro()
{
    unsigned char cmdZeroz[] = {0xff, 0xaa, 0x52};
    unsigned char cmdUseSerial[] = {0xff, 0xaa, 0x61};
    unsigned char cmdUseI2C[] = {0xff, 0xaa, 0x62};
    unsigned char cmdBaud115200[] = {0xff, 0xaa, 0x63};
    unsigned char cmdBaude9600[] = {0xff, 0xaa, 0x64};

    try
    {
        int wrlen = write(sfd, cmdZeroz, sizeof (cmdZeroz));
        if (wrlen != sizeof (cmdZeroz)) 
            throw runtime_error("write cmdZeros failed: "+std::to_string(errno));
        wrlen = write(sfd, cmdUseSerial, sizeof (cmdZeroz));
        if (wrlen != sizeof (cmdUseSerial)) 
            throw runtime_error("write cmdUseSerial failed: "+std::to_string(errno));
        wrlen = write(sfd, cmdBaude9600, sizeof (cmdZeroz));
        if (wrlen != sizeof (cmdBaude9600)) 
            throw runtime_error("write cmdBaude9600 failed: "+std::to_string(errno));

    } catch (const std::exception& ex)
    {
        std::string msg( std::string("XPilotView: GyroManager::initGyro() : ") + ex.what());
        XPilotViewUtils::logMessage(msg);
    }
}

void GyroManager::decode(unsigned char buf[], float result[])
{
    if (buf[0] == 0x55)
    {
        switch (buf [1]) {
            case 0x51:
                result[0] = (short(buf [3] << 8 | buf [2])) / 32768.0 * 16;
                result[1] = (short(buf [5] << 8 | buf [4])) / 32768.0 * 16;
                result[2] = (short(buf [7] << 8 | buf [6])) / 32768.0 * 16;
                break;
            case 0x52:
                result[0] = (short(buf [3] << 8 | buf [2])) / 32768.0 * 2000;
                result[1] = (short(buf [5] << 8 | buf [4])) / 32768.0 * 2000;
                result[2] = (short(buf [7] << 8 | buf [6])) / 32768.0 * 2000;
                break;
            case 0x53:
                result[0] = (short(buf [3] << 8 | buf [2])) / 32768.0 * 180;
                result[1] = (short(buf [5] << 8 | buf [4])) / 32768.0 * 180;
                result[2] = (short(buf [7] << 8 | buf [6])) / 32768.0 * 180;
                break;
        }
    }
}

