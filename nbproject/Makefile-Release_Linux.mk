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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release_Linux
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/source/Map.o \
	${OBJECTDIR}/source/StateGame.o \
	${OBJECTDIR}/source/StateMenu.o \
	${OBJECTDIR}/source/debug.o \
	${OBJECTDIR}/source/draw_text.o \
	${OBJECTDIR}/source/life.o \
	${OBJECTDIR}/source/main.o \
	${OBJECTDIR}/source/network.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lallegro -lallegro_primitives -lallegro_font -lallegro_image -lallegro_ttf

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/life-multi

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/life-multi: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/life-multi ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/source/Map.o: nbproject/Makefile-${CND_CONF}.mk source/Map.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Map.o source/Map.cpp

${OBJECTDIR}/source/StateGame.o: nbproject/Makefile-${CND_CONF}.mk source/StateGame.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/StateGame.o source/StateGame.cpp

${OBJECTDIR}/source/StateMenu.o: nbproject/Makefile-${CND_CONF}.mk source/StateMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/StateMenu.o source/StateMenu.cpp

${OBJECTDIR}/source/debug.o: nbproject/Makefile-${CND_CONF}.mk source/debug.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/debug.o source/debug.cpp

${OBJECTDIR}/source/draw_text.o: nbproject/Makefile-${CND_CONF}.mk source/draw_text.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/draw_text.o source/draw_text.cpp

${OBJECTDIR}/source/life.o: nbproject/Makefile-${CND_CONF}.mk source/life.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/life.o source/life.cpp

${OBJECTDIR}/source/main.o: nbproject/Makefile-${CND_CONF}.mk source/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/main.o source/main.cpp

${OBJECTDIR}/source/network.o: nbproject/Makefile-${CND_CONF}.mk source/network.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/network.o source/network.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/life-multi

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
