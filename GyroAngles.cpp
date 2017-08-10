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
        this->x = 0.0;
        this->y = 0.0;
        this->z = 0.0;
    }

    GyroAngles::GyroAngles(float ax, float ay, float az)
    {
        this->x = ax;
        this->y = ay;
        this->z = az;
    }

    GyroAngles::~GyroAngles()
    {
    }
    
    void GyroAngles::setAngles(float ax, float ay, float az)
    {
        this->x = ax;
        this->y = ay;
        this->z = az;
    }
    
    void GyroAngles::setAngles(double ax, double ay, double az)
    {
        this->x = ax;
        this->y = ay;
        this->z = az;
    }
    
    void GyroAngles::setAngles(AngleSet a)
    {
        this->x = a.x;
        this->y = a.y;
        this->z = a.z;
    }
    
    AngleSet GyroAngles::getAngleSet()
    {
        AngleSet result = {this->x, this->y, this->z};
        return result;
    }

