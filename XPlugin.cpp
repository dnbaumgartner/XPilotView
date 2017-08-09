/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "XPlugin.hpp"


GyroManager gmgr;
bool preferencesVisible = false;

void mainMenuHandler(void *, void *);

PLUGIN_API int XPluginStart(
        char * outName,
        char * outSig,
        char * outDesc)
{
    XPLMMenuID mainMenu;
    int pluginMenuItem;

    strcpy(outName, "XPilotView");
    strcpy(outSig, "com.antelopevisuals.xpilotview");
    strcpy(outDesc, "Controls pilot's view from a head mounted gyro.");

    //XPLMDebugString("Before getTTyPath\n");
    //std::string ttypath = gmgr.getTTyPath();
    //XPLMDebugString("After getTTyPath\n");

    pluginMenuItem = XPLMAppendMenuItem(XPLMFindPluginsMenu(), "XPilotView", NULL, 1);
    mainMenu = XPLMCreateMenu("XPilotView", XPLMFindPluginsMenu(), pluginMenuItem, mainMenuHandler, NULL);
    XPLMAppendMenuItem(mainMenu, "Preferences", (void*) "Preferences", 1);
   
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
    if (preferencesVisible)
    {
        preferencesVisible = false;
    }
}

/*
 * XPluginDisable
 * 
 */
PLUGIN_API void XPluginDisable(void)
{
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
        gmgr.showPreferences(true);
    }
}
