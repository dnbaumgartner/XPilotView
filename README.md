# XPilotView

An MEMS Gyroscope based head tracker for X-Plane 11. 

This head tracker is yet another variation on the utility of controlling the pilots view in the X-Plane simulator window by moving the sim pilots head in desired orientations. Other head trackers have been developed using infrared emitters and reflectors on the pilots head which are then tracked with an infrared web cam and associated software drivers. Other head trackers use some variation of image recognition to track head movements and orientations which are translated into sim view commands.

Previous implementations of gyroscope-based head tracking have generally used smart phone internal gyros as the sensor. The MEMS gyroscope used in this project has made low cost gyro head tracking possible.

## Development Environment

### OS, IDE, Compilers
The development environment and target operating environment is Linux. There no plans for iOS or Windows versions.

The development OS is Linux Mint 18.1 (Ubuntu 16.04) which is also the testing and operating platform.

The code base is configured for NetBeans IDE 18.1 with the C/C++ plugin. The Makefile as configured by NetBeans also works as a standalone build tool.

The compiler base is the GNU Compiler Collection version 5.4.0.

### Additional Software

The 64-bit [X-Plane SDK 2.1.3](http://www.xsquawkbox.net/xpsdk/mediawiki/Main_Page). 

## Parts List

### Gyro

[BWT901 MPU6050 Accelerometer Gyroscope](https://www.amazon.com/gp/product/B018NNAZW8/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1)

### USB Interface

[USB TTL 232 485 converter serial module](https://www.amazon.com/gp/product/B01CNW061U/ref=oh_aui_detailpage_o05_s00?ie=UTF8&psc=1)

### Flat Cable

[Ribbon cable](https://www.amazon.com/gp/product/B007R9SQQM/ref=od_aui_detailpages00?ie=UTF8&psc=1)

### Connectors

[Hilitchi 2.54mm Pin Connector Kit](https://www.amazon.com/gp/product/B012EOO9Q0/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1)

[Crimping tool](https://www.amazon.com/gp/product/B00OMM4YUY/ref=pe_2640190_232748420_pd_te_o_mr_ti/144-0462194-4486716?_encoding=UTF8&pd_rd_i=B00OMM4YUY&pd_rd_r=ZRGQVRTNCG1R04RESCV2&pd_rd_w=FX2O9&pd_rd_wg=pk4xY)



## Software Design

The major components of the design are the following classes:
* XPlugin:
* GyroManager:
* PreferencesManager:
* PreferencesPanel:

Helper classes are:
* GyroAngles:
* KeyValueStore:
* XPilotViewUtils:

QT 5 in a pthread isolates the GUI from the X-Plane runtime system.

## Deployment

### X-Plane Setup

## Operation

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Dave Baumgartner** 

## License

This project is licensed under the GNU General Public License Version 3 or later.

See the [COPYING](COPYING) file for details

## Acknowledgments

* Inspiration
