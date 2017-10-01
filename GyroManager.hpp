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
 * File:   GyroManager.hpp
 * Author: dave
 *
 * Created on August 4, 2017, 8:58 PM
 */

#ifndef GYROMANAGER_HPP
#define GYROMANAGER_HPP

#include <string>
#include <cmath>
#include <exception>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include "GyroAngles.hpp"
#include "PreferencesManager.hpp"
#include "KeyValueStore.hpp"

class GyroManager {

    struct termios savetty;


    PreferencesManager prefMgr;

public:
    GyroManager();
    virtual ~GyroManager();

    void start();
    void stop();
    GyroAnglesPtr getAngles();
    void showPreferencesPanel(bool);
    void setViewCenter();
    void calibrateGyroOffset();
    void togglePreferencesPanel();
    static void decode(unsigned char buf[], float result[]);
    
    static float rateoffset[3];
    static bool calibrateGyro;
    static bool isRunning;
    static bool resetCenterView;
    static unsigned int sfd;
    static GyroAngles viewCenter;
    static GyroAnglesPtr angles;
    static float normalizeAngle(float a);

private:

    void startManagerThread();
    unsigned int opentty(std::string ttyPath);
    void initGyro();

};

#endif /* GYROMANAGER_HPP */

