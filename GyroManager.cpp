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
        this->startManagerThread();
        this->isRunning = true;

    } catch (const std::exception& ex)
    {
        std::string msg(std::string("XPilotView: GyroManager::start() : ") + ex.what());
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
        std::string msg(std::string("XPilotView: GyroManager::stop() : ") + ex.what());
        XPilotViewUtils::logMessage(msg);
    }
}

GyroAnglesPtr GyroManager::getAngles()
{
    return GyroManager::angles;
}

void GyroManager::showPreferencesPanel(bool show)
{
    prefMgr.showPanel(show);
}

void GyroManager::togglePreferencesPanel()
{
    prefMgr.togglePanel();
}

void GyroManager::setViewCenter()
{
    setCenterView = true;
}

void *GyroManagerThread(void *arg)
{
    KeyValueStore* preferences = KeyValueStore::Instance();

    unsigned char buf[80];
    float a[3];
    AngleSet lastAngle = {0.0, 0.0, 0.0};

    float logHeadAngle;
    float logViewAngle;

    float rollCurvature;
    float pitchCurvature;
    float headingCurvature;

    float roll;
    float pitch;
    float heading;

    float filterLag;
    
    try
    {
        string shAngle = preferences->getValue("targetHeadAngle");
        string svAngle = preferences->getValue("targetViewAngle");
        float hAngle = std::stof(shAngle);
        float vAngle = std::stof(svAngle);
        logHeadAngle = std::log10(hAngle);
        logViewAngle = std::log10(vAngle);

        string srcurve = preferences->getValue("rollCurvature");
        rollCurvature = std::stof(srcurve);
        string spcurve = preferences->getValue("pitchCurvature");
        pitchCurvature = std::stof(spcurve);
        string shcurve = preferences->getValue("headingCurvature");
        headingCurvature = std::stof(shcurve);

        string slag = preferences->getValue("filterLag");
        filterLag = std::stof(slag);

    } catch (const std::exception& ex)
    {
        std::string msg(std::string("XPilotView: GyroManager::GyroManagerThread():initializing curvatures : ") + ex.what());
        XPilotViewUtils::logMessage(msg);
    }

    while (GyroManager::isRunning)
    {
        int rdlen = read(GyroManager::sfd, buf, 1);

        if (rdlen > 0)
        {
            if (buf[0] == 0x55)
            {
                rdlen = read(GyroManager::sfd, &buf[1], 10);
                
                if (buf[1] == 0x53) // this is the angles frame
                {
                    try
                    {
                        GyroManager::decode(buf, a);

                        // normalize to the range -90, +90
                        a[0] = GyroManager::normalizeAngle(a[0]);
                        a[1] = GyroManager::normalizeAngle(a[1]);
                        a[2] = GyroManager::normalizeAngle(a[2]);
                        
                        // apply smoothing
                        float deltaA = a[0] - lastAngle.roll;
                        lastAngle.roll = lastAngle.roll + deltaA / filterLag;
                        deltaA = a[1] - lastAngle.pitch;
                        lastAngle.pitch = lastAngle.pitch + deltaA / filterLag;
                        deltaA = a[2] - lastAngle.heading;
                        lastAngle.heading = lastAngle.heading + deltaA / filterLag;

                        // center the view point
                        AngleSet center = GyroManager::viewCenter.getAngleSet();
                        roll = (lastAngle.roll - center.roll);
                        pitch = (lastAngle.pitch - center.pitch);
                        heading = (lastAngle.heading - center.heading);

                    } catch (const std::exception& ex)
                    {
                        std::string msg(std::string("XPilotView: GyroManager::GyroManagerThread():processing angle values : ") + ex.what());
                        XPilotViewUtils::logMessage(msg);
                    }

                    // Apply exponential acceleration to the head angle
                    // to yield an accelerated view angle.
                    //
                    // The formula is:
                    //
                    // viewangle = (headangle^curvature) / scale
                    // 
                    // Where scale can be calculated for a target head angle 
                    // and view angle via:
                    //
                    //  scale = 10^(log(targetHeadAngle) * curvature - log(targetViewAngle)))
                    //
                    //  For a target headAngle=20 and viewAngle=90:
                    //
                    //  scale = 10^(1.3*curvature - 1.95))
                    //
                    //  This yields a curve such that a head deflection of
                    //  20 degrees yields a view deflection of 90 degrees.
                    //  Varing the value of curvature does not change the
                    //  target angles but only changes the curvature of the
                    //  transform.
                    //
                    try
                    {
                        float e = logHeadAngle * headingCurvature - logViewAngle;
                        float scale = pow(10.0, e);
                        bool sign = signbit(heading);
                        heading = std::pow(abs(heading), headingCurvature) / scale;
                        heading = (sign ? heading : -heading);

                        e = logHeadAngle * pitchCurvature - logViewAngle;
                        scale = pow(10.0, e);
                        sign = signbit(pitch);
                        pitch = pow(abs(pitch), pitchCurvature) / scale;
                        pitch = (sign ? pitch : -pitch);

                        e = logHeadAngle * rollCurvature - logViewAngle;
                        scale = pow(10.0, e);
                        sign = signbit(roll);
                        roll = pow(abs(roll), rollCurvature) / scale;
                        roll = (sign ? -roll : roll);

                    } catch (const std::exception& ex)
                    {
                        std::string msg(std::string("XPilotView: GyroManager::GyroManagerThread():applying curvature function : ") + ex.what());
                        XPilotViewUtils::logMessage(msg);
                    }

                    // angles object will be shared with and read by XPlugin loop
                    GyroManager::angles->setAngles(roll, pitch, heading);

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
        std::string ttypath = KeyValueStore::Instance()->getValue("ttyPath");
        sfd = this->opentty(ttypath);
        this->initGyro();

        pthread_t gmthread;
        int ret = 0;

        ret = pthread_create(&gmthread, NULL, &GyroManagerThread, NULL);

    } catch (const std::exception& ex)
    {
        std::string msg(std::string("XPilotView: GyroManager::startManagerThread() : ") + ex.what());
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
        std::string msg(std::string("XPilotView: GyroManager::opentty() : ") + ex.what());
        XPilotViewUtils::logMessage(msg);
    }

    return sfd;
}

void GyroManager::initGyro()
{
    unsigned char cmdBaud115200[] = {0xff, 0xaa, 0x04, 0x06, 0x00};
    unsigned char cmdRate100[] = {0xff, 0xaa, 0x03, 0x09, 0x00};
    unsigned char cmdSave[] = {0xff, 0xaa, 0x00, 0x00, 0x00};

    try
    {
        int wrlen = write(sfd, cmdBaud115200, sizeof (cmdBaud115200));
        if (wrlen != sizeof (cmdBaud115200))
            throw runtime_error("write cmdBaud115200 failed: " + std::to_string(errno));
        wrlen = write(sfd, cmdRate100, sizeof (cmdRate100));
        if (wrlen != sizeof (cmdRate100))
            throw runtime_error("write cmdRate100 failed: " + std::to_string(errno));
        wrlen = write(sfd, cmdSave, sizeof (cmdSave));
        if (wrlen != sizeof (cmdSave))
            throw runtime_error("write cmdSave failed: " + std::to_string(errno));

    } catch (const std::exception& ex)
    {
        std::string msg(std::string("XPilotView: GyroManager::initGyro() : ") + ex.what());
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

