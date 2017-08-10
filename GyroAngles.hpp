/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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
    float x;
    float y;
    float z;
};

class GyroAngles {
    float x;
    float y;
    float z;

public:
    GyroAngles();
    GyroAngles(float x, float y, float z);
    virtual ~GyroAngles();
    
    void setAngles(float x, float y, float z);
    void setAngles(double x, double y, double z);
    void setAngles(AngleSet);
    AngleSet getAngleSet();
    
private:
    AngleSet gangles;
};

typedef std::shared_ptr<GyroAngles> GyroAnglesPtr;

#endif /* GYROANGLES_HPP */

