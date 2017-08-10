/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "XPlugin.hpp"

GyroManager gyroMgr;
bool preferencesVisible = false;

void mainMenuHandler(void *, void *);

GyroAnglesPtr gyroAngles;

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

    pluginMenuItem = XPLMAppendMenuItem(XPLMFindPluginsMenu(), "XPilotView", NULL, 1);
    mainMenu = XPLMCreateMenu("XPilotView", XPLMFindPluginsMenu(), pluginMenuItem, mainMenuHandler, NULL);
    XPLMAppendMenuItem(mainMenu, "Preferences", (void*) "Preferences", 1);
   
    gyroAngles = gyroMgr.getAngles();
    
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
