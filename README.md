# XPilotView

A MEMS Gyroscope based head tracker for X-Plane 11. 

This head tracker is yet another variation on the utility of controlling the pilots view in the X-Plane simulator window by moving the sim pilots head in desired orientations. Other head trackers have been developed using infrared emitters and reflectors on the pilots head which are then tracked with an infrared web cam and associated software drivers. Other head trackers use some variation of image recognition to track head movements and orientations which are translated into sim view commands.

Previous implementations of gyroscope-based head tracking have generally used smart phone internal gyros as the sensor. The MEMS gyroscope used in this project has made low cost gyro head tracking possible.

## Supported platforms

XPilotView is developed for Linux 64-bit systems only. See the Development Environment section for the specific OS and library versions. There are no plans for creating an iOS or Windows version.

## Deployment

The built plugin is stored as dist/Debug/XPilotView/64/lin.xpl. Copy the XPilotView/64/lin.xpl directory tree into the X-Plane resources/plugins folder. In addition, a tarball of the current release is available in dist/XPilotView.1.0.0.tar.gz. Simple unpack the tarball into the resources/plugins folder.

## Operation

### Configuring the Gyro

### Gyro Sensor Installation

### X-Plane Setup

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
The main theme of the software design is to execute all functions of the plugin in isolation from the X-Plane runtime threading system. The principle function of the XPlugin is simply to asyncronously fetch computed view angles and write the same to the appropriate X-Plane variables. All GUI operations are performed by threaded QtApplication classes and all interactions with the gyro device and subsequent computations execute in the context of a dedicated thread.

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
