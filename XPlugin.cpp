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


#include "XPlugin.hpp"

PLUGIN_API int XPluginStart(
        char * outName,
        char * outSig,
        char * outDesc)
{
    XPLMMenuID mainMenu;
    int pluginMenuItem;

    strcpy(outName, "XPilotView");
    strcpy(outSig, "com.antelopevisuals.xpilotview.0.1");
    strcpy(outDesc, "Controls pilot's view from a head mounted gyro.");

    // Menu setup
    pluginMenuItem = XPLMAppendMenuItem(
            XPLMFindPluginsMenu(),
            "XPilotView",
            NULL,
            1);
    mainMenu = XPLMCreateMenu(
            "XPilotView",
            XPLMFindPluginsMenu(),
            pluginMenuItem,
            mainMenuHandler,
            NULL);
    XPLMAppendMenuItem(
            mainMenu,
            "Preferences",
            (void*) "Preferences",
            1);
    XPLMAppendMenuItem(
            mainMenu,
            "Calibrate Gyro",
            (void*) "Calibrate Gyro",
            1);

    // Custom commands
    XPLMCommandRef centerViewCommand = XPLMCreateCommand(
            "XPilotView/View/Center",
            "Set current view as view center.");

    XPLMRegisterCommandHandler(
            centerViewCommand,
            CenterViewCommandHandler,
            1, // process before x-plane
            (void *) 0);

    XPLMCommandRef startStopCommand = XPLMCreateCommand(
            "XPilotView/View/StartStop",
            "Start/Stop view head tracking.");

    XPLMRegisterCommandHandler(
            startStopCommand,
            StartStopCommandHandler,
            1, // process before x-plane
            (void *) 0);

    XPLMCommandRef calibrateOffsetCommand = XPLMCreateCommand(
            "XPilotView/View/CalibrateOffset",
            "Calibrate gyro for offset drift.");

    XPLMRegisterCommandHandler(
            calibrateOffsetCommand,
            CalibrateOffsetCommandHandler,
            1, // process before x-plane
            (void *) 0);

    gyroAngles = gyroMgr.getAngles();

    pilotsHeadPsi = XPLMFindDataRef("sim/graphics/view/pilots_head_psi"); // yaw
    pilotsHeadThe = XPLMFindDataRef("sim/graphics/view/pilots_head_the"); // pitch
    pilotsHeadPhi = XPLMFindDataRef("sim/graphics/view/pilots_head_phi"); // roll

    return 1;
}

/*
 * XPluginStop
 * 
 * Our cleanup routine deallocates our window.
 * 
 */
PLUGIN_API void XPluginStop(void)
{
    XPLMUnregisterFlightLoopCallback(FlightLoopCallback, NULL);
    if (gyroMgr.isRunning)
    {
        gyroMgr.stop();
    }
    XPLMDebugString("XPilotView: stopped.");
}

/*
 * XPluginDisable
 * 
 */
PLUGIN_API void XPluginDisable(void)
{
    XPLMDebugString("XPilotView: disabled.");
}

/*
 * XPluginEnable.
 * 
 */
PLUGIN_API int XPluginEnable(void)
{
    return 1;
}

/*
 * XPluginReceiveMessage
 * 
 */
PLUGIN_API void XPluginReceiveMessage(
        XPLMPluginID inFromWho,
        int inMessage,
        void * inParam)
{
}

void mainMenuHandler(void *menu, void *item)
{
    if (std::string((char*) item) == "Preferences")
    {
        gyroMgr.showPreferencesPanel(true);
    }
    if (std::string((char*) item) == "Calibrate Gyro")
    {
        gyroMgr.calibrateGyroOffset();
    }
}

int CenterViewCommandHandler(XPLMCommandRef cmdRef, XPLMCommandPhase phase, void *refcon)
{
    if (phase == xplm_CommandEnd)
    {
        gyroMgr.setViewCenter();
    }
    return 0;
}

int StartStopCommandHandler(XPLMCommandRef cmdRef, XPLMCommandPhase phase, void *refcon)
{
    if (phase == xplm_CommandEnd)
    {
        if (GyroManager::isRunning)
        {
            XPLMUnregisterFlightLoopCallback(FlightLoopCallback, NULL);
            gyroMgr.stop();
        } else
        {
            gyroMgr.start();
            XPLMRegisterFlightLoopCallback(
                    FlightLoopCallback,
                    LOOPTIME,
                    NULL);
        }
    }
    return 0;
}

int CalibrateOffsetCommandHandler(XPLMCommandRef cmdRef, XPLMCommandPhase phase, void *refcon)
{
    if (phase == xplm_CommandEnd)
    {
        gyroMgr.calibrateGyroOffset();
    }
    return 0;
}

float FlightLoopCallback(
        float timeFromLastCall,
        float timeFromLastFlightLoop,
        int counter,
        void * refcon)
{
    AngleSet angles = gyroAngles->getAngleSet();

    // The sensor is mounted 90 degrees off the forward/aft center line so the 
    // computed roll becomes the pitch. We'll set the commanded roll
    // value to zero. We do this because there is cross talk between the
    // computed yaw and pitch channels such that varying the pitch will
    // induce a yaw change. So we rotate the sensor 90 degrees and use the 
    // computed yaw and roll values which have no interaction for the 
    // commanded yaw and pitch and fix the commanded roll to zero.
    //
    XPLMSetDataf(pilotsHeadPsi, angles.yaw);    // command yaw
    XPLMSetDataf(pilotsHeadThe, angles.pitch);   // command pitch
    XPLMSetDataf(pilotsHeadPhi, angles.roll);           // command roll

    return LOOPTIME;
}
