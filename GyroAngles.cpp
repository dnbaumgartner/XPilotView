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
 * File:   GyroAngles.cpp
 * Author: dave
 * 
 * Created on August 4, 2017, 9:20 PM
 */

#include "GyroAngles.hpp"

    
    GyroAngles::GyroAngles()
    {
        this->roll = 0.0;
        this->pitch = 0.0;
        this->heading = 0.0;
    }

    GyroAngles::GyroAngles(float roll, float pitch, float heading)
    {
        this->roll = roll;
        this->pitch = pitch;
        this->heading = heading;
    }

    GyroAngles::~GyroAngles()
    {
    }
    
    void GyroAngles::setAngles(float roll, float pitch, float heading)
    {
        this->roll = roll;
        this->pitch = pitch;
        this->heading = heading;
    }
    
    void GyroAngles::setAngles(double roll, double pitch, double heading)
    {
        this->roll = roll;
        this->pitch = pitch;
        this->heading = heading;
    }
    
    void GyroAngles::setAngles(AngleSet a)
    {
        this->roll = a.roll;
        this->pitch = a.pitch;
        this->heading = a.heading;
    }
    
    AngleSet GyroAngles::getAngleSet()
    {
        AngleSet result = {this->roll, this->pitch, this->heading};
        return result;
    }

