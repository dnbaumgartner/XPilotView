/*
 * This file is part of XPilotView.
 *
 * XPilotView is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XPilotView is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XPilotView.  If not, see <http://www.gnu.org/licenses/>
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
#include <iostream>

#include "XPLMUtilities.h"
#include "XPLMProcessing.h"
#include "XPLMDataAccess.h"
#include "XPLMMenus.h"
#include "XPWidgets.h"
#include "XPStandardWidgets.h"
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"

#include "GyroManager.hpp"

#define LOOPTIME 0.03

int CenterViewCommandHandler(XPLMCommandRef, XPLMCommandPhase, void *);
int StartStopCommandHandler(XPLMCommandRef, XPLMCommandPhase, void *);
void mainMenuHandler(void *, void *);

GyroManager gyroMgr;
bool preferencesVisible = false;
GyroAnglesPtr gyroAngles;

static XPLMDataRef pilotsHeadPsi;
static XPLMDataRef pilotsHeadThe;
static XPLMDataRef pilotsHeadPhi;

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


float FlightLoopCallback(
        float timeFromLastCall,
        float timeFromLastFlightLoop,
        int counter,
        void * refcon);

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

