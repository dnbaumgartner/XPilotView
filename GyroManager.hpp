/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include "GyroAngles.hpp"
#include "PreferencesManager.hpp"

class GyroManager {
public:
    GyroManager();
    virtual ~GyroManager();

    void start();
    void stop();
    GyroAnglesPtr getAngles();
    void showPreferences(bool);
    std::string getTTyPath();
    
    static void decode(unsigned char buf[], float result[]);

private:

    static std::string ttyPath;
    static bool isRunnable;
    
    void startManagerThread();
    unsigned int opentty(std::string ttyPath);
    void initGyro();

};

#endif /* GYROMANAGER_HPP */

