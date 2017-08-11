/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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

    gyroAngles = gyroMgr.getAngles();

    pilotsHeadPsi = XPLMFindDataRef("sim/graphics/view/pilots_head_psi"); // heading
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
        gyroMgr.showPreferences(true);
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

float FlightLoopCallback(
        float timeFromLastCall,
        float timeFromLastFlightLoop,
        int counter,
        void * refcon)
{
    AngleSet angles = gyroAngles->getAngleSet();
    
    XPLMSetDataf(pilotsHeadPsi, angles.heading);
    XPLMSetDataf(pilotsHeadThe, angles.pitch);
    XPLMSetDataf(pilotsHeadPhi, angles.roll);
    
    return LOOPTIME;
}