/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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

