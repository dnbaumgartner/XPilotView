#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/d2f23c52/GyroAngles.o \
	${OBJECTDIR}/_ext/d2f23c52/GyroManager.o \
	${OBJECTDIR}/_ext/d2f23c52/PreferencesManager.o \
	${OBJECTDIR}/_ext/d2f23c52/XPilotViewUtils.o \
	${OBJECTDIR}/_ext/d2f23c52/XPlugin.o \
	${OBJECTDIR}/KeyValueStore.o \
	${OBJECTDIR}/PreferencesPanel.o \
	${OBJECTDIR}/moc_PreferencesPanel.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -fPIC -fvisibility=hidden -D_REENTRANT -m64 -std=c++11 -pthread
CXXFLAGS=-m64 -fPIC -fvisibility=hidden -D_REENTRANT -m64 -std=c++11 -pthread

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=--64 -D_REENTRANT

# Link Libraries and Options
LDLIBSOPTIONS=/usr/lib/x86_64-linux-gnu/libQt5Core.so /usr/lib/x86_64-linux-gnu/libQt5Gui.so /usr/lib/x86_64-linux-gnu/libQt5Widgets.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ./dist/${CONF}/${PROJECTNAME}/64/lin.xpl

./dist/${CONF}/${PROJECTNAME}/64/lin.xpl: /usr/lib/x86_64-linux-gnu/libQt5Core.so

./dist/${CONF}/${PROJECTNAME}/64/lin.xpl: /usr/lib/x86_64-linux-gnu/libQt5Gui.so

./dist/${CONF}/${PROJECTNAME}/64/lin.xpl: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so

./dist/${CONF}/${PROJECTNAME}/64/lin.xpl: ${OBJECTFILES}
	${MKDIR} -p ./dist/${CONF}/${PROJECTNAME}/64
	gcc -o ./dist/${CONF}/${PROJECTNAME}/64/lin.xpl ${OBJECTFILES} ${LDLIBSOPTIONS} -D_REENTRANT -m64 -static-libgcc -shared -Wl,--version-script=exports.txt -Wl,-rpath=\$$\ORIGIN -Wl,-z,origin

${OBJECTDIR}/_ext/d2f23c52/GyroAngles.o: /home/dave/NetBeansProjects/XPilotView/GyroAngles.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d2f23c52
	${RM} "$@.d"
	$(COMPILE.cc) -g -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2f23c52/GyroAngles.o /home/dave/NetBeansProjects/XPilotView/GyroAngles.cpp

${OBJECTDIR}/_ext/d2f23c52/GyroManager.o: /home/dave/NetBeansProjects/XPilotView/GyroManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d2f23c52
	${RM} "$@.d"
	$(COMPILE.cc) -g -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2f23c52/GyroManager.o /home/dave/NetBeansProjects/XPilotView/GyroManager.cpp

${OBJECTDIR}/_ext/d2f23c52/PreferencesManager.o: /home/dave/NetBeansProjects/XPilotView/PreferencesManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d2f23c52
	${RM} "$@.d"
	$(COMPILE.cc) -g -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2f23c52/PreferencesManager.o /home/dave/NetBeansProjects/XPilotView/PreferencesManager.cpp

${OBJECTDIR}/_ext/d2f23c52/XPilotViewUtils.o: /home/dave/NetBeansProjects/XPilotView/XPilotViewUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d2f23c52
	${RM} "$@.d"
	$(COMPILE.cc) -g -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2f23c52/XPilotViewUtils.o /home/dave/NetBeansProjects/XPilotView/XPilotViewUtils.cpp

${OBJECTDIR}/_ext/d2f23c52/XPlugin.o: /home/dave/NetBeansProjects/XPilotView/XPlugin.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d2f23c52
	${RM} "$@.d"
	$(COMPILE.cc) -g -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2f23c52/XPlugin.o /home/dave/NetBeansProjects/XPilotView/XPlugin.cpp

${OBJECTDIR}/KeyValueStore.o: KeyValueStore.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/KeyValueStore.o KeyValueStore.cpp

${OBJECTDIR}/PreferencesPanel.o: PreferencesPanel.cpp ui_PreferencesPanel.h
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PreferencesPanel.o PreferencesPanel.cpp

moc_PreferencesPanel.cpp: PreferencesPanel.hpp 
	@echo Performing Custom Build Step
	/usr/lib/x86_64-linux-gnu/qt5/bin/moc -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/include/c++/5 -I/usr/include/x86_64-linux-gnu/c++/5 -I/usr/include/c++/5/backward -I/usr/lib/gcc/x86_64-linux-gnu/5/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/5/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include PreferencesPanel.hpp -o moc_PreferencesPanel.cpp

ui_PreferencesPanel.h: PreferencesPanel.ui 
	@echo Performing Custom Build Step
	/usr/lib/x86_64-linux-gnu/qt5/bin/uic PreferencesPanel.ui -o ui_PreferencesPanel.h

${OBJECTDIR}/moc_PreferencesPanel.o: moc_PreferencesPanel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/moc_PreferencesPanel.o moc_PreferencesPanel.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ./dist/${CONF}/${PROJECTNAME}/64/lin.xpl
	${RM} moc_PreferencesPanel.cpp
	${RM} ui_PreferencesPanel.h

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
