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
    float roll; 
    float pitch;
    float heading;
};

class GyroAngles {
    float roll; 
    float pitch;
    float heading;

public:
    GyroAngles();
    GyroAngles(float roll, float pitch, float heading);
    virtual ~GyroAngles();
    
    void setAngles(float roll, float pitch, float heading);
    void setAngles(double roll, double pitch, double heading);
    void setAngles(AngleSet);
    AngleSet getAngleSet();
    
private:
    AngleSet gangles;
};

typedef std::shared_ptr<GyroAngles> GyroAnglesPtr;

#endif /* GYROANGLES_HPP */

