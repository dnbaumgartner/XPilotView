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
 * File:   GyroAngles.hpp
 * Author: dave
 *
 * Created on August 4, 2017, 9:20 PM
 */

#ifndef GYROANGLES_HPP
#define GYROANGLES_HPP

#include <memory>


struct AngleSet
{
    float roll; 
    float pitch;
    float yaw;
};

class GyroAngles {
    float roll; 
    float pitch;
    float yaw;

public:
    GyroAngles();
    GyroAngles(float roll, float pitch, float yaw);
    virtual ~GyroAngles();
    
    void setAngles(float roll, float pitch, float yaw);
    void setAngles(double roll, double pitch, double yaw);
    void setAngles(AngleSet);
    AngleSet getAngleSet();
    
private:
    
};

typedef std::shared_ptr<GyroAngles> GyroAnglesPtr;

#endif /* GYROANGLES_HPP */

