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

    GyroAngles::GyroAngles(GyroAngles* orig)
    {
        this->x = orig->x;
        this->y = orig->y;
        this->z = orig->z;
    }

    GyroAngles::GyroAngles(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    GyroAngles::~GyroAngles()
    {
    }
    
    float GyroAngles::x;
    float GyroAngles::y;
    float GyroAngles::z;

