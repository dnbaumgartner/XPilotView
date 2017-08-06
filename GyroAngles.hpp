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

class GyroAngles {
public:
    GyroAngles();
    GyroAngles(GyroAngles* orig);
    GyroAngles(float x, float y, float z);
    virtual ~GyroAngles();
    
    static float x;
    static float y;
    static float z;
    
private:
    
};

typedef std::shared_ptr<GyroAngles> GyroAnglesPtr;

#endif /* GYROANGLES_HPP */

