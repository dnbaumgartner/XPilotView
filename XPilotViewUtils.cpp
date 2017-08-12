/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XPilotViewUtils.cpp
 * Author: dave
 * 
 * Created on August 12, 2017, 2:51 PM
 */

#include "XPilotViewUtils.hpp"

XPilotViewUtils::XPilotViewUtils()
{
}

XPilotViewUtils::~XPilotViewUtils()
{
}

void XPilotViewUtils::logMessage(std::string msg)
{
    XPLMDebugString(msg.c_str());
}

void XPilotViewUtils::logMessage(char* msg)
{
    XPLMDebugString(msg);
}
