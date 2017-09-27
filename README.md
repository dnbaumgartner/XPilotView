# XPilotView (DRAFT)

A MEMS Gyroscope based head tracker for X-Plane 11. 

This head tracker is yet another variation on the utility of controlling the pilots view in the X-Plane simulator window by moving the sim pilots head in desired orientations. Other head trackers have been developed using infrared emitters and reflectors on the pilots head which are then tracked with an infrared web cam and associated software drivers. Other head trackers use some variation of image recognition to track head movements and orientations which are translated into sim view commands.

Previous implementations of gyroscope-based head tracking have generally used smart phone internal gyros as the sensor. The MEMS gyroscope used in this project has made low cost gyro head tracking possible.

The small size (thumbnail) of the MEMS gyroscope allows to mount the device on the pilots head in such a way to capture the yaw and pitch motions. One mounting method is to fasten (tape?) the MEMS device to the inside top of a cap which then is worn on the pilots head.

## Supported platforms

XPilotView is developed for Linux 64-bit systems only. See the Development Environment section for the specific OS and library versions. There are no plans for creating an iOS or Windows version.

## Deployment

The built plugin is stored as dist/Debug/XPilotView/64/lin.xpl. 

Copy the XPilotView/64/lin.xpl directory tree into the X-Plane resources/plugins folder. 

In addition, a tarball of the current release is available in dist/XPilotView.1.0.0.tar.gz. Simple unpack the tarball into the resources/plugins folder.

## Operation

### Configuring the Gyro

The user manual, setup guide, Android app .apk and other (Windows, ARM) app versions can be found at:
https://drive.google.com/file/d/0B8PmY6nhQadKLWdxN2VNY1E1OWc/view

Other useful information can be found in the Amazon questions section:
https://www.amazon.com/MPU6050-Bluetooth-Accelerometer-Gyroscope-Four-rotor/dp/B018NNAZW8#Ask

The following instructions are for the Android app. Other platform version have not been tried.

1) Install the MiniIMUEn.apk in your Android phone. 
1) Plug the USB connector into the host computer.
1) Connect the app with the gyro. This app will communicate with the JY-901 gyro over Bluetooth.
1) Here are the settings for the Config panel:
   * Module Type: JY-901Serial
   * Output Content: Gyro
   * Output Rate: 50Hz
1) Switching to the Data panel and selecting Gyro, you should see Axis data change as you tilt the gyro about the three axis.
1) This setup need only to be done once as the settings are stored on the gyro. However, it is interesting to play with other settings and data channels to see the effect of manipulating the gyro.
 

### Gyro Sensor Installation

As mentioned previously, this developer mounted the gyro module on the inside top of a hat.

The orientation of the gyro is critical. Please note the photo of the gyro module in the following Parts List section.
 * The side of the module shown in the picture will be oriented as the bottom side next to the head. The Bluetooth antenna side will be on the top next to the cap.
 * The gyro module should be rotated so that the X-Axis (Roll) arrow in the photo should be pointing to the left side of the head.
 * The gyro connector side should be on the right.

This particular orientation is so because we're using the Roll axis to measure the head pitch instead of the Pitch axis. The Pitch axis has some not well understood interaction with the Yaw axis that we can ignore if we use the Roll axis instead.

The connector pins on the gyro module are inconvenient because they protrude at right angles to the module board and conflict with the head space inside the cap. This developer soldered new pins that extend to the side and clipped off the original pins.

Once the device and software are working correctly, the gyro and USB modules can be protected with shrink tubing from your local Frys Electronics.

### X-Plane Setup

### XPilotView Settings

## Parts List

Here is the list of the necessary hardware parts. You must have sufficient skill and experience to fabricate the ribbon cable and connector parts as well as understanding the user manual that describes the gyro hookup. This document will not go into any additional detail beyond what is written here.

### Gyro

[BWT901 MPU6050 Accelerometer Gyroscope](https://www.amazon.com/gp/product/B018NNAZW8/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1)

<img src="https://github.com/dnbaumgartner/XPilotView/blob/master/images/JY901Gyro.jpg" width="400" height="400">

### USB Interface

[USB TTL 232 485 converter serial module](https://www.amazon.com/gp/product/B01CNW061U/ref=oh_aui_detailpage_o05_s00?ie=UTF8&psc=1)

### Wire Cable

[Ribbon cable](https://www.amazon.com/gp/product/B007R9SQQM/ref=od_aui_detailpages00?ie=UTF8&psc=1)

### Connectors

[Hilitchi 2.54mm Pin Connector Kit](https://www.amazon.com/gp/product/B012EOO9Q0/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1)

[Crimping tool](https://www.amazon.com/gp/product/B00OMM4YUY/ref=pe_2640190_232748420_pd_te_o_mr_ti/144-0462194-4486716?_encoding=UTF8&pd_rd_i=B00OMM4YUY&pd_rd_r=ZRGQVRTNCG1R04RESCV2&pd_rd_w=FX2O9&pd_rd_wg=pk4xY)

## Development Environment

### OS, IDE, Compilers
The development environment and target operating environment is Linux. There no plans for iOS or Windows versions.

The development OS is Linux Mint 18.1 (Ubuntu 16.04) which is also the testing and operating platform.

The code base is configured for NetBeans IDE 18.1 with the C/C++ plugin. The Makefile as configured by NetBeans also works as a standalone build tool.

The compiler base is the GNU Compiler Collection version 5.4.0.

Qt application development framework, version 5.5.

### Additional Software

The 64-bit [X-Plane SDK 2.1.3](http://www.xsquawkbox.net/xpsdk/mediawiki/Main_Page). 

## Software Design
The main theme of the software design is to execute all functions of the plugin in isolation from the X-Plane runtime threading system in order to minimize any perturbations of the X-Plane cycle time. The principle function of the XPlugin module is then to simply and asyncronously fetch computed view angles and write the same to the appropriate X-Plane variables. All GUI operations are performed by threaded QtApplication classes and all interactions with the gyro device and subsequent computations execute in the context of a dedicated thread independent of the X-Plane runtime.

The major components of the design are the following classes:
* XPlugin:
  * Interface to X-Plane.
  * Writes computed head angles to X-Plane view angle variables.
  * Passes X-Plane Start/Stop, View Center and Preferences menu commands to the plugin main codes.

* GyroManager:
  * Manages gyro read thread (Start/Stop) in isolation from the X-Plane runtime.
  * Handles X-Plane preferences menu request.
  * Computes transfer function mapping physical head movements to view commands.

* PreferencesManager:
  * Initializes and show/hides the Preferences panel.
  * Runs the QApplication Preferences panel in a pthread in isolation from the X-Plane runtime.
  * Manages the stored preferences file.

* PreferencesPanel:
  * Instanciates the PreferencesPanel object from the Qt .ui configuration.

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

* Inspiration
