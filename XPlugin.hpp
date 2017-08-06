/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XPlugin.hpp
 * Author: Dave Baumgartner
 *
 * Created on August 4, 2017, 8:56 PM
 */

#ifndef XPLUGIN_HPP
#define XPLUGIN_HPP

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "XPLMUtilities.h"
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"

#include "GyroManager.hpp"

static XPLMWindowID gWindow = NULL;
static bool mouseDown = false;

static void MyDrawWindowCallback(
        XPLMWindowID inWindowID,
        void * inRefcon);

static void MyHandleKeyCallback(
        XPLMWindowID inWindowID,
        char inKey,
        XPLMKeyFlags inFlags,
        char inVirtualKey,
        void * inRefcon,
        int losingFocus);

static int MyHandleMouseClickCallback(
        XPLMWindowID inWindowID,
        int x,
        int y,
        XPLMMouseStatus inMouse,
        void * inRefcon);

PLUGIN_API int XPluginStart(
        char * outName,
        char * outSig,
        char * outDesc);

PLUGIN_API void XPluginStop(void);

PLUGIN_API void XPluginDisable(void);

PLUGIN_API int XPluginEnable(void);

PLUGIN_API void XPluginReceiveMessage(
        XPLMPluginID inFromWho,
        int inMessage,
        void * inParam);

#endif /* XPLUGIN_HPP */

