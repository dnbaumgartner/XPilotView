# XPilotView Version 1.0

A MEMS Gyroscope based head tracker for X-Plane 11. 

The XPilotView head tracker is yet another variation on the utility of controlling the pilots view in the X-Plane simulator window by sensing the motion of the sim pilots head. Other head trackers have been developed using infrared emitters and reflectors on the pilots head which are then tracked with an infrared web cam and associated software drivers. Also, other head trackers use some variation of image recognition to track head movements and orientations which are translated into sim view commands.

Previous implementations of gyroscope-based head tracking have generally used smart phone internal gyros as the sensor. The MEMS gyroscope used in this project has made low cost gyro head tracking possible.

The small size of the MEMS gyroscope allows to mount the device on the pilots head in such a way as to capture the pilots head yaw and pitch motions. One mounting method is to fasten (tape?) the MEMS device to the inside top of a cap which then is worn on the pilots head.

## Supported platforms

XPilotView is developed for Linux 64-bit systems only. See the Development Environment section for the specific OS and library versions. There are no plans for creating an iOS or Windows version.

## Deployment

The plugin is built and stored in dist/Debug/XPilotView/64/lin.xpl in the development tree. 

Copy the XPilotView/64/lin.xpl directory tree into the X-Plane resources/plugins folder. 

In addition, a tarball of the current release is available in dist/XPilotView.1.0.0.tar.gz. Simple unpack the tarball into the resources/plugins folder.

## Operation

The goals of this version of XPilotView are:
  * Provide reliable, accurate head tracking input to X-Plane with minimal external gear.
  * Capture only the yaw and pitch head motions as angular data. Xyz head displacements are not computed in this version.
  * Provide a start/stop control input via a joystick/keyboard button.
  * Provide a view recentering action via a joystick/keyboard button.
  * Provide a gyro rate offset calibration via the XPilotView menu in X-Plane.
  * Implement a low sensitivity zone around the view center point with increasing sensitivity away from the center point.

The low sensitivity zone requires an explanation. It was found with early versions of this software that the gyro was very sensitive and given a linear response to head movements, the view would move around in response to slight head movements. This proved to be distracting during focused periods of flight such as landing, maneuvering and instrument scans. The solution was to implement a nonlinear transfer function mapping the head position to the view position such that the transfer function has a low gain in the region surrounding the centered view position and an accelerating gain as head moves further away from the centered position.

### Connecting the Gyro

The gyro module is connected to the USB serial adapter via a flat cable and connector pins as listed in the **Parts List** section. You should allow for a sufficient length of ribbon cable to reach from the pilots head to the USB port of the simulation computer. When the gyro module and USB adapter are wired correctly per the user manual, the module receives power from the 5 volt pinout of the USB serial convertor. Since the gyro performs a self-calibration on power up, it is important that the **module should be kept stationary on a stable surface during the short powerup sequence (a few seconds)**. If the gyro experiences any motion or vibration during this phase, the gyro may be calibrated with an offset in one or more of the rate axis. 

### Configuring the Gyro

The user manual, setup guide, Android app .apk and other (Windows, ARM) app versions can be found at:
https://drive.google.com/file/d/0B8PmY6nhQadKLWdxN2VNY1E1OWc/view

Other useful information can be found in the Amazon questions section:
https://www.amazon.com/MPU6050-Bluetooth-Accelerometer-Gyroscope-Four-rotor/dp/B018NNAZW8#Ask

The following instructions are for the Android app.

1) Install the MiniIMUEn.apk in your Android phone. This app will be listed in your app matrix as "Billiard".
1) Plug the USB connector into the host computer.
1) Connect the app with the gyro. This app will communicate with the JY-901 gyro over Bluetooth.
1) Here are the settings for the Config panel:
   * Module Type: JY-901Serial
   * Output Content: Gyro
   * Output Rate: 50Hz
1) Switching to the Data panel and selecting Gyro, you should see the axis data change as you tilt the gyro about the three axis.
1) This setup need only to be done once as the settings are stored on the gyro. However, it is interesting to play with other settings and data channels to see the effect of manipulating the gyro.

### Calibrating the Gyro

The gyro occasionally develops an offset in one of the rate axis. This is indicated when the centerpoint of the view drifts while your head/gyro is held in a fixed position. Clicking the zeroing button will temporarily return the view to the center position but drifts off again. 

The gyro offset can be recalibrated either from the X-Plane XPilotView menu setting as described in the following **XPilotView Settings** section or by the following steps using the Android Billiard (MiniIMUEn) app:

1) As before, plug the USB adapter into the host computer while maintaining the gyro module on a stable surface.
1) Connect the Billiard app (MiniIMUEn.apk) to the gyro.
1) Select the Config display.
1) Set the gyro module on a stationary surface in an orientation similar to the operating orientation.
1) Touch the "Gyro Calibrate" bar in the Config display.
1) Select 'OK' to calibrate.
1) Wait for a stable display on all three axis. The numbers may jitter by a few tenths or hundredths which is ok.
1) Touch the "OK" bar in the Config display.
1) The gyro offset will be saved and the drifting of the viewpoint should be gone.
1) If the drift persists then there may be a fault in the gyro. I have never observed an offset that could not be corrected with calibration.

### Gyro Sensor Installation

As mentioned previously, I mount the gyro module on the inside top of a cap.

The orientation of the gyro is critical. Please note the photo of the gyro module in the following Parts List section.
 * The side of the module shown in the picture will be oriented as the bottom side next to the head. The Bluetooth antenna side will be the up side next to the inside of the cap.
 * The gyro module should be rotated so that the X-Axis (Roll) arrow in the photo should be pointing to the left side of the head.
 * The gyro connector side should be on the right.

This particular orientation is so because we're using the Roll axis to measure the head pitch instead of the Pitch axis. The Pitch axis has some not well understood interaction with the Yaw axis that we can ignore if we use the Roll axis for head pitch instead.

The connector pins on the gyro module are inconvenient because they protrude at right angles to the module board and conflict with the head space inside the cap. I modified the connection by soldering new pins that extend to the side and clipped off the original pins.

Once the device and software are working correctly, the gyro and USB modules can be protected with shrink tubing from your local Frys Electronics.

### X-Plane Setup

If the XPilotView plugin is loaded correctly by X-Plane, an XPilotView menu entry will appear in the Plugin menu selection of the X-Plane menu bar.

There are two XPilotView/X-Plane variables that are convenient to bind to joystick or keyboard buttons:
```text
XPilotView/
    View/
        Set current view as view center
        StartStop view head tracking
```
I use a Microsoft Sidewinder Precision Pro joystick and it is useful to bind button 1 to the **Set current view as view center** and button 8 to **StartStop view head tracking**. I have found that while head tracking is in effect, it is common to set the view center several times as your head position adjusts to accomodate flight activity. Also, it is convenient to have the tracking start/stop available on the joy stick base within easy reach.

### XPilotView Settings

The XPilotView menu will have two selections: **Preferences** and **Calibrate Gyro**.

The **Calibrate Gyro** selection will force a recalibration of the gyro rate offset values. This recalibration will take approximately three seconds and the X-Plane view will be frozen during the recalibration. If head tracking is active, it will be stopped and must be manually restarted if desired. As with any calibration event, it is necessary that the gyro be placed securely on a stable surface. Having the gyro fixed to your head and keeping your head still during the calibration is not good enough and will almost guarantee an offset drift.

The menu **Preferences** selection will present a Preferences Panel for changing some preference values:
  * TTY Path - The serial tty port assigned to the USB serial adapter.
  * Yaw Curvature - Determines the degree of the yaw null zone around the view center. Reasonable values to use are 1.2 to 1.9. A higher number creates a more extreme curve.
  * Pitch Curvature - Determines the degree of the pitch null zone around the view center.
  * Roll Curvature - Not used at this time.
  * Smoothing - Roughly represents the number of gyro measurements to average over. Use higher values for very smooth but slower response time and lower values for more responsive behavior but possibly more jitter.

A default preferences configuration file will be created when the plugin is initialized by X-Plane for the first time. The location of this file is in the X-Plane directory as: 

**Output/preferences/XPilotViewPrefs.json**

This file is updated by the Preferences Panel during a save but also can be updated by manual editing of the values. Any changes to the preference values will not take effect until the tracking is stopped and started again.

The file is in Json format. If the format is munged during a manual edit the plugin will throw an error. One should always create a backup before editing. The default file is configured like so:

```text
{
    "filterLag": "10.0",
    "pitchCurvature": "1.8",
    "rollCurvature": "1.8",
    "samplePeriod": "0.02",
    "targetHeadAngle": "20",
    "targetViewAngle": "90",
    "ttyPath": "/dev/ttyUSB0",
    "yawCurvature": "1.5"
}
```
Note that there are two additional preferences not shown in the GUI Preferences Panel: **targetHeadAngle** and **targetViewAngle**. The values for these settings are in degrees of rotation for both yaw and pitch. These settings map a head yaw angle to a corresponding view yaw angle such that, in the default setting, a head movement to 20 degrees from center will result in a view movement to 90 degrees from center. Because of the nonlinear transfer function described earlier, the view offcenter angle of 90 will occur exactly at a head offcenter angle of 20 and any other deflection relationships will depend on the values of the curvature settings.

## Parts List

Here is the list of the necessary hardware parts. You must have sufficient skill and experience to fabricate the ribbon cable and connector parts as well as understanding the user manual that describes the gyro hookup. This document will not go into any additional detail beyond what is written here.

### Gyro

[BWT901 MPU6050 Accelerometer Gyroscope](https://www.amazon.com/gp/product/B018NNAZW8/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1)

<img src="https://github.com/dnbaumgartner/XPilotView/blob/master/images/JY901Gyro.jpg" width="400" height="400">

### USB Interface

[USB TTL 232 485 converter serial module](https://www.amazon.com/gp/product/B01CNW061U/ref=oh_aui_detailpage_o05_s00?ie=UTF8&psc=1)

### Wire Cable

[Ribbon cable](https://www.amazon.com/gp/product/B007R9SQQM/ref=od_aui_detailpages00?ie=UTF8&psc=1)

Since there are only four pins on each end to be connected, a four wire strip of the ribbon can be ripped off the wider ribbon. This will make a more flexible and convenient connecting cable.

### Connectors

[Hilitchi 2.54mm Pin Connector Kit](https://www.amazon.com/gp/product/B012EOO9Q0/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1)

[Crimping tool](https://www.amazon.com/gp/product/B00OMM4YUY/ref=pe_2640190_232748420_pd_te_o_mr_ti/144-0462194-4486716?_encoding=UTF8&pd_rd_i=B00OMM4YUY&pd_rd_r=ZRGQVRTNCG1R04RESCV2&pd_rd_w=FX2O9&pd_rd_wg=pk4xY)

## Development Environment

### OS, IDE, Compilers
The development environment and target operating environment is Linux. There are no plans for iOS or Windows versions.

The development OS is Linux Mint 18.1 (Ubuntu 16.04) which is also the testing and operating platform.

The code base is configured for NetBeans IDE 8.1 with the C/C++ plugin. The Makefile as configured by NetBeans also works as a standalone build tool.

The compiler base is the GNU Compiler Collection version 5.4.0.

The GUI is built on the Qt application development framework, version 5.5.

### Additional Software

The 64-bit [X-Plane SDK 2.1.3](http://www.xsquawkbox.net/xpsdk/mediawiki/Main_Page). 

JSON for Modern C++: https://github.com/nlohmann/json  (included in the XPilotView source tree)

## Software Design
The main theme of the software design is to execute all functions of the plugin in isolation from the X-Plane runtime threading system in order to minimize any perturbations of the X-Plane cycle time. The principle function of the XPlugin module is then to asyncronously fetch computed view angles from a shared data object and write the angles to the appropriate X-Plane variables. All GUI operations are performed by threaded QtApplication classes and all interactions with the gyro device and subsequent computations execute in the context of a dedicated thread independent of the X-Plane runtime.

The major components of the design are the following classes:
* XPlugin:
  * Interface to X-Plane.
  * Writes computed head angles to X-Plane view angle variables.
  * Passes X-Plane Start/Stop, View Center action events and Preferences menu commands to the plugin main codes.

* GyroManager:
  * Manages the gyro read thread (Start/Stop) in isolation from the X-Plane runtime.
  * Handles X-Plane preferences menu requests.
  * Computes the transfer function that maps physical head movements to view commands.

* PreferencesManager:
  * Initializes and show/hides the Preferences panel.
  * Runs the QApplication Preferences panel in a pthread in isolation from the X-Plane runtime.
  * Manages the stored preferences file.

* PreferencesPanel:
  * Instantiates the PreferencesPanel object from the Qt .ui configuration file. The .ui file is developed and maintained by QT Designer.

Helper classes are:
* GyroAngles:
  * Container for roll, pitch and yaw angles.
  
* KeyValueStore:
  * Provides get/set operations on the stored preferences file.
  
* XPilotViewUtils:
  * Utility static functions

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/dnbaumgartner/XPilotView/tags). 

## Authors

* **Dave Baumgartner** 

## License

This project is licensed under the GNU General Public License Version 3 or later.

See the [COPYING](COPYING) file for details

## Acknowledgments

* Many thanks to Bob "Blue Side Up" Feaver for encouraging me to take look at X-Plane plugin development.
