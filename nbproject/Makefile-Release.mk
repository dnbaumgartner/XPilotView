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
CND_CONF=Release
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
	${OBJECTDIR}/Madgwick.o \
	${OBJECTDIR}/PreferencesPanel.o \
	${OBJECTDIR}/moc_PreferencesPanel.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-fPIC -fvisibility=hidden -m64
CXXFLAGS=-fPIC -fvisibility=hidden -m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ./dist/${CONF}/${PROJECTNAME}/64/lin.xpl

./dist/${CONF}/${PROJECTNAME}/64/lin.xpl: ${OBJECTFILES}
	${MKDIR} -p ./dist/${CONF}/${PROJECTNAME}/64
	gcc -o ./dist/${CONF}/${PROJECTNAME}/64/lin.xpl ${OBJECTFILES} ${LDLIBSOPTIONS} -m64 -static-libgcc -shared -Wl,--version-script=exports.txt

${OBJECTDIR}/_ext/d2f23c52/GyroAngles.o: /home/dave/NetBeansProjects/XPilotView/GyroAngles.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d2f23c52
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2f23c52/GyroAngles.o /home/dave/NetBeansProjects/XPilotView/GyroAngles.cpp

${OBJECTDIR}/_ext/d2f23c52/GyroManager.o: /home/dave/NetBeansProjects/XPilotView/GyroManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d2f23c52
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2f23c52/GyroManager.o /home/dave/NetBeansProjects/XPilotView/GyroManager.cpp

${OBJECTDIR}/_ext/d2f23c52/PreferencesManager.o: /home/dave/NetBeansProjects/XPilotView/PreferencesManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d2f23c52
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2f23c52/PreferencesManager.o /home/dave/NetBeansProjects/XPilotView/PreferencesManager.cpp

${OBJECTDIR}/_ext/d2f23c52/XPilotViewUtils.o: /home/dave/NetBeansProjects/XPilotView/XPilotViewUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d2f23c52
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2f23c52/XPilotViewUtils.o /home/dave/NetBeansProjects/XPilotView/XPilotViewUtils.cpp

${OBJECTDIR}/_ext/d2f23c52/XPlugin.o: /home/dave/NetBeansProjects/XPilotView/XPlugin.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d2f23c52
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2f23c52/XPlugin.o /home/dave/NetBeansProjects/XPilotView/XPlugin.cpp

${OBJECTDIR}/KeyValueStore.o: KeyValueStore.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/KeyValueStore.o KeyValueStore.cpp

${OBJECTDIR}/Madgwick.o: Madgwick.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Madgwick.o Madgwick.cpp

${OBJECTDIR}/PreferencesPanel.o: PreferencesPanel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PreferencesPanel.o PreferencesPanel.cpp

${OBJECTDIR}/moc_PreferencesPanel.o: moc_PreferencesPanel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM200=1 -DXPLM210=1 -I./SDK/CHeaders/XPLM -I./SDK/CHeaders/Widgets -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/moc_PreferencesPanel.o moc_PreferencesPanel.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ./dist/${CONF}/${PROJECTNAME}/64/lin.xpl

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
