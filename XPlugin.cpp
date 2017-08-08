/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "XPlugin.hpp"


GyroManager gmgr;
bool preferencesVisible = false;

XPWidgetID preferencesWidget = NULL;
XPWidgetID preferencesWindow = NULL;
XPWidgetID preferencesTextWidget[50] = {NULL};

void mainMenuHandler(void *, void *);
XPWidgetID createPreferencesWindow(int xl, int yl, int w, int h);
int preferencesHandler(XPWidgetMessage msg, XPWidgetID widget, long p1, long p2);

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

    std::string ttypath = gmgr.getTTyPath();

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
        XPDestroyWidget(preferencesWidget, 1);
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
        if (preferencesWidget == NULL)
        {
            preferencesWidget = createPreferencesWindow(50, 72, 400, 500);
        }
        XPShowWidget(preferencesWidget);

        std::cout << "XPilotView:mainMenuHandler:after showWidget: widgetid=" << preferencesWidget << std::endl;
    }
}

XPWidgetID createPreferencesWindow(int xl, int yl, int w, int h)
{
    std::cout << "XPilotView: in createPreferencesWindow\n" << std::endl;
    int x2 = xl + w;
    int y2 = yl - h;
    
    XPWidgetID mainWidgetId = XPCreateWidget(
            xl, yl, x2, y2, // window extent
            1, // visible
            "XPilotView Preferences", // descriptor
            1, // is root window
            NULL, // no parent for root window
            xpWidgetClass_MainWindow // main window class
            );

    XPSetWidgetProperty(mainWidgetId, xpProperty_MainWindowHasCloseBoxes, 1);
    XPAddWidgetCallback(mainWidgetId, preferencesHandler);

    XPWidgetID subWindow = XPCreateWidget(
            xl + 5, yl - 4, x2 - 50, y2 + 30,
            1, // Visible
            "", // desc
            0, // not root
            mainWidgetId, // child of main window
            xpWidgetClass_SubWindow);

    XPSetWidgetProperty(subWindow, xpProperty_SubWindowType, xpSubWindowStyle_SubWindow);

    std::cout << "XPilotView: exiting createPreferencesWindow\n" << std::endl;
    
    return mainWidgetId;
}

int preferencesHandler(XPWidgetMessage msg, XPWidgetID widget, long p1, long p2)
{
    if (msg = xpMessage_CloseButtonPushed)
    {
        if (preferencesVisible)
        {
            XPHideWidget(preferencesWidget);
        }
        return 1;
    }
    return 0;
}
