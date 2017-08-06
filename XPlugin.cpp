/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "XPlugin.hpp"


GyroManager gmgr;

/*
 * XPluginStart
 * 
 * Our start routine registers our window and does any other initialization we 
 * must do.
 * 
 */
PLUGIN_API int XPluginStart(
        char * outName,
        char * outSig,
        char * outDesc)
{
    strcpy(outName, "XPilotView");
    strcpy(outSig, "com.antelopevisuals.xpilotview");
    strcpy(outDesc, "Controls pilot's view from a head mounted gyro.");

    std::string ttypath = gmgr.getTTyPath();

    gWindow = XPLMCreateWindow(
            50, 600, 300, 200, /* Area of the window. */
            1, /* Start visible. */
            MyDrawWindowCallback, /* Callbacks */
            MyHandleKeyCallback,
            MyHandleMouseClickCallback,
            NULL); /* Refcon - not used. */

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
    XPLMDestroyWindow(gWindow);
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

/*
 * MyDrawingWindowCallback
 * 
 * This callback does the work of drawing our window once per sim cycle each time
 * it is needed.  It dynamically changes the text depending on the saved mouse
 * status.  Note that we don't have to tell X-Plane to redraw us when our text
 * changes; we are redrawn by the sim continuously.
 * 
 */
void MyDrawWindowCallback(
        XPLMWindowID inWindowID,
        void * inRefcon)
{
    int left, top, right, bottom;
    float color[] = {1.0, 1.0, 1.0}; /* RGB White */

    /* First we get the location of the window passed in to us. */
    XPLMGetWindowGeometry(inWindowID, &left, &top, &right, &bottom);

    /* We now use an XPLMGraphics routine to draw a translucent dark
     * rectangle that is our window's shape. */
    XPLMDrawTranslucentDarkBox(left, top, right, bottom);

    /* Finally we draw the text into the window, also using XPLMGraphics
     * routines.  The NULL indicates no word wrapping. */
    XPLMDrawString(color, left + 5, top - 20,
            (char*) (mouseDown ? "I'm a plugin" : "Hello world"), NULL, xplmFont_Basic);

}

/*
 * MyHandleKeyCallback
 * 
 * Our key handling callback does nothing in this plugin.  This is ok; 
 * we simply don't use keyboard input.
 * 
 */
void MyHandleKeyCallback(
        XPLMWindowID inWindowID,
        char inKey,
        XPLMKeyFlags inFlags,
        char inVirtualKey,
        void * inRefcon,
        int losingFocus)
{
}

/*
 * MyHandleMouseClickCallback
 * 
 * Our mouse click callback toggles the status of our mouse variable 
 * as the mouse is clicked.  We then update our text on the next sim 
 * cycle.
 * 
 */
int MyHandleMouseClickCallback(
        XPLMWindowID inWindowID,
        int x,
        int y,
        XPLMMouseStatus inMouse,
        void * inRefcon)
{
    /* If we get a down or up, toggle our status click.  We will
     * never get a down without an up if we accept the down. */
    if (inMouse == xplm_MouseDown)
    {
        mouseDown = true;
    } else if (inMouse == xplm_MouseUp)
    {
        mouseDown = false;
    }

    /* Returning 1 tells X-Plane that we 'accepted' the click; otherwise
     * it would be passed to the next window behind us.  If we accept
     * the click we get mouse moved and mouse up callbacks, if we don't
     * we do not get any more callbacks.  It is worth noting that we 
     * will receive mouse moved and mouse up even if the mouse is dragged
     * out of our window's box as long as the click started in our window's 
     * box. */
    return 1;
}