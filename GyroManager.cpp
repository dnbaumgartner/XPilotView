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
#include "MadgwickAHRS.h"


#define TIME 0x50
#define ACCEL 0x51
#define GYRO 0x52
#define ANGLE 0x53
#define MAGN 0x54

struct vec3
{
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
};

struct rotation
{
    float pitch = 0.0;
    float roll = 0.0;
    float yaw = 0.0;
};

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

    Madgwick madgwick;
    madgwick.begin(50.0);

    unsigned char buf[80];
    float a[3];
    AngleSet lastAngle = {0.0, 0.0, 0.0};

    float logHeadAngle;
    float logViewAngle;

    float rollCurvature;
    float pitchCurvature;
    float yawCurvature;

    float roll;
    float pitch;
    float yaw;

    struct vec3 accel;
    struct vec3 gyro;
    struct vec3 magn;

    struct rotation raw;
    struct rotation smoothed;
    struct rotation extended;

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
        string shcurve = preferences->getValue("yawCurvature");
        yawCurvature = std::stof(shcurve);

        string slag = preferences->getValue("filterLag");
        filterLag = std::stof(slag);

        GyroManager::setCenterView = true;

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

                if (buf[1] == GYRO)
                {
                    GyroManager::decode(buf, a);

                    raw.roll += 0.02 * a[0];
                    raw.pitch += 0.02 * a[1];
                    raw.yaw += 0.02 * a[2];

                    try
                    {
                        // get new center values if commanded
                        if (GyroManager::setCenterView)
                        {
                            // zero the integrated raw angles to correct for drift
                            raw.roll = 0.0;
                            raw.pitch = 0.0;
                            raw.yaw = 0.0;
                            
                            GyroManager::viewCenter.setAngles(raw.roll, raw.pitch, raw.yaw);
                            GyroManager::setCenterView = false;
                        }

                        // center the view point
                        AngleSet center = GyroManager::viewCenter.getAngleSet();
                        smoothed.roll = raw.roll - center.roll;
                        smoothed.pitch = raw.pitch - center.pitch;
                        smoothed.yaw = raw.yaw - center.yaw;
                        //printf("roll: %4.3f pitch: %4.3f yaw: %4.3f\n", smoothed.roll, smoothed.pitch, smoothed.yaw);

                        // apply smoothing
                        float diff = smoothed.roll - lastAngle.roll;
                        lastAngle.roll = lastAngle.roll + diff / filterLag;
                        smoothed.roll = lastAngle.roll;
                        
                        diff = smoothed.pitch - lastAngle.pitch;
                        lastAngle.pitch = lastAngle.pitch + diff / filterLag;
                        smoothed.pitch = lastAngle.pitch;
                        
                        diff = smoothed.yaw - lastAngle.yaw;
                        lastAngle.yaw = lastAngle.yaw + diff / filterLag;
                        smoothed.yaw = lastAngle.yaw;

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
                        float e = logHeadAngle * yawCurvature - logViewAngle;
                        float scale = pow(10.0, e);
                        bool sign = signbit(smoothed.yaw);
                        extended.yaw = std::pow(abs(smoothed.yaw), yawCurvature) / scale;
                        extended.yaw = (sign ? extended.yaw : -extended.yaw);

                        e = logHeadAngle * pitchCurvature - logViewAngle;
                        scale = pow(10.0, e);
                        sign = signbit(smoothed.pitch);
                        extended.pitch = pow(abs(smoothed.pitch), pitchCurvature) / scale;
                        extended.pitch = (sign ? extended.pitch : -extended.pitch);

                        e = logHeadAngle * rollCurvature - logViewAngle;
                        scale = pow(10.0, e);
                        sign = signbit(smoothed.roll);
                        extended.roll = pow(abs(smoothed.roll), rollCurvature) / scale;
                        extended.roll = (sign ? extended.roll : -extended.roll);

                    } catch (const std::exception& ex)
                    {
                        std::string msg(std::string("XPilotView: GyroManager::GyroManagerThread():applying curvature function : ") + ex.what());
                        XPilotViewUtils::logMessage(msg);
                    }

                    // angles object will be shared with and read by the XPlugin loop
                    //
                    GyroManager::angles->setAngles(extended.roll, extended.pitch, extended.yaw);
                }
            }
        }
    }

    GyroManager::isRunning = false;
}

float GyroManager::normalizeAngle(float a)
{
    float result = a;

    while (result < -180.0)
    {
        result += 180.0;
    }
    while (180.0 < result)
    {
        result -= 180.0;
    }

    //    if (-180.0 < a && a < -90.0)
    //    {
    //        result = a + 180.0;
    //    } else if (90.0 < a && a < 180)
    //    {
    //        result = a - 180.0;
    //    }

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
            case ACCEL:
                result[0] = (short(buf [3] << 8 | buf [2])) / 32768.0 * 16.0;
                result[1] = (short(buf [5] << 8 | buf [4])) / 32768.0 * 16.0;
                result[2] = (short(buf [7] << 8 | buf [6])) / 32768.0 * 16.0;
                break;
            case GYRO:
                result[0] = (short(buf [3] << 8 | buf [2])) / 32768.0 * 2000.0;
                result[1] = (short(buf [5] << 8 | buf [4])) / 32768.0 * 2000.0;
                result[2] = (short(buf [7] << 8 | buf [6])) / 32768.0 * 2000.0;
                break;
            case ANGLE:
                result[0] = (short(buf [3] << 8 | buf [2])) / 32768.0 * 180.0;
                result[1] = (short(buf [5] << 8 | buf [4])) / 32768.0 * 180.0;
                result[2] = (short(buf [7] << 8 | buf [6])) / 32768.0 * 180.0;
                break;
            case MAGN:
                result[0] = float(short(buf [3] << 8 | buf [2]));
                result[1] = float(short(buf [5] << 8 | buf [4]));
                result[2] = float(short(buf [7] << 8 | buf [6]));
                break;
        }
    }
}

