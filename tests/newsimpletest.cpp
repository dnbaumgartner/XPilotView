/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest.cpp
 * Author: dave
 *
 * Created on August 5, 2017, 11:48 AM
 */

#include <stdlib.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "GyroManager.hpp"

/*
 * Simple C++ Test Suite
 */

void test1()
{
    std::cout << "newsimpletest test 1" << std::endl;
    GyroManager gm;

    gm.start();

    for (int i = 0; i<40000; i++)
    {
        GyroAnglesPtr angles = gm.getAngles();
        //std::cout << "Test1 Angles: " << angles->x << " " << angles->y << " " << angles->z << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    gm.stop();
}

void test2()
{
    std::cout << "newsimpletest test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (newsimpletest) message=error message sample" << std::endl;
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (newsimpletest)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (newsimpletest)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (newsimpletest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

