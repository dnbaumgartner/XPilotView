/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XPilotViewUtils.hpp
 * Author: dave
 *
 * Created on August 12, 2017, 2:51 PM
 */

#ifndef XPILOTVIEWUTILS_HPP
#define XPILOTVIEWUTILS_HPP

#include <string>
#include "XPLMUtilities.h"

class XPilotViewUtils {
    
public:
    XPilotViewUtils();
    virtual ~XPilotViewUtils();
    
    static void logMessage(std::string msg);
    static void logMessage(char* msg);
    
private:

};

#endif /* XPILOTVIEWUTILS_HPP */

