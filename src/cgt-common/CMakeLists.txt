#
# Console Guitar Tuner (CGT)
# Copyright (c) 2011 by Bloody.Rabbit
#
# Author: Bloody.Rabbit
#

################
# Dependencies #
################
CHECK_INCLUDE_FILE( "inttypes.h" HAVE_INTTYPES_H )

FIND_PACKAGE( "ALSA" REQUIRED )
FIND_PACKAGE( "FFTW3" REQUIRED )

# As it's not an *actual* subdirectory, CMake forces us
# to specify the binary directory as well ...
ADD_SUBDIRECTORY( "${PROJECT_SOURCE_DIR}/dep/tinyxml"
                  "${PROJECT_BINARY_DIR}/dep/tinyxml" )

##############
# Initialize #
##############
SET( TARGET_NAME        "cgt-common" )
SET( TARGET_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/${TARGET_NAME}" )
SET( TARGET_SOURCE_DIR  "${PROJECT_SOURCE_DIR}/src/${TARGET_NAME}" )

SET( TARGET_INCLUDE_DIRS
     ${ALSA_INCLUDE_DIRS}
     ${FFTW3_INCLUDE_DIRS}
     ${tinyxml_INCLUDE_DIRS}
     "${TARGET_INCLUDE_DIR}" )

# Export the include directories
SET( ${TARGET_NAME}_INCLUDE_DIRS ${TARGET_INCLUDE_DIRS} PARENT_SCOPE )

#########
# Files #
#########
SET( INCLUDE
     "${TARGET_INCLUDE_DIR}/cgt-common.h"
     "${TARGET_INCLUDE_DIR}/cgt-compat.h" )
SET( SOURCE
     "${TARGET_SOURCE_DIR}/cgt-compat.cpp" )

SET( alsa_INCLUDE
     "${TARGET_INCLUDE_DIR}/alsa/Pcm.h"
     "${TARGET_INCLUDE_DIR}/alsa/Pcm.inl" )
SET( alsa_SOURCE
     "" )

SET( config_INCLUDE
     "${TARGET_INCLUDE_DIR}/config/ArgvParser.h"
     "${TARGET_INCLUDE_DIR}/config/ConfigMgr.h"
     "${TARGET_INCLUDE_DIR}/config/XmlParser.h" )
SET( config_SOURCE
     "${TARGET_SOURCE_DIR}/config/ArgvParser.cpp"
     "${TARGET_SOURCE_DIR}/config/XmlParser.cpp" )

SET( core_INCLUDE
     "${TARGET_INCLUDE_DIR}/core/Analyser.h"
     "${TARGET_INCLUDE_DIR}/core/FftAnalyser.h" )
SET( core_SOURCE
     "${TARGET_SOURCE_DIR}/core/Analyser.cpp"
     "${TARGET_SOURCE_DIR}/core/FftAnalyser.cpp" )

SET( db_INCLUDE
     "${TARGET_INCLUDE_DIR}/db/IField.h"
     "${TARGET_INCLUDE_DIR}/db/IParameter.h"
     "${TARGET_INCLUDE_DIR}/db/TextValue.h"
     "${TARGET_INCLUDE_DIR}/db/TextValue.inl" )
SET( db_SOURCE
     "${TARGET_SOURCE_DIR}/db/TextValue.cpp" )

SET( except_INCLUDE
     "${TARGET_INCLUDE_DIR}/except/Except.h"
     "${TARGET_INCLUDE_DIR}/except/Except.inl" )
SET( except_SOURCE
     "" )

SET( stats_INCLUDE
     "${TARGET_INCLUDE_DIR}/stats/Derivative.h"
     "${TARGET_INCLUDE_DIR}/stats/Derivative.inl"
     "${TARGET_INCLUDE_DIR}/stats/ICounter.h"
     "${TARGET_INCLUDE_DIR}/stats/IFilter.h"
     "${TARGET_INCLUDE_DIR}/stats/Maximum.h"
     "${TARGET_INCLUDE_DIR}/stats/Maximum.inl"
     "${TARGET_INCLUDE_DIR}/stats/Periodic.h"
     "${TARGET_INCLUDE_DIR}/stats/Periodic.inl" )
SET( stats_SOURCE
     "" )

SET( util_INCLUDE
     "${TARGET_INCLUDE_DIR}/util/Harmonics.h"
     "${TARGET_INCLUDE_DIR}/util/Misc.h"
     "${TARGET_INCLUDE_DIR}/util/SafeMem.h"
     "${TARGET_INCLUDE_DIR}/util/Singleton.h"
     "${TARGET_INCLUDE_DIR}/util/Tone.h" )
SET( util_SOURCE
     "${TARGET_SOURCE_DIR}/util/Harmonics.cpp"
     "${TARGET_SOURCE_DIR}/util/Misc.cpp"
     "${TARGET_SOURCE_DIR}/util/Tone.cpp" )

########################
# Setup the executable #
########################
INCLUDE_DIRECTORIES( ${TARGET_INCLUDE_DIRS} )

SOURCE_GROUP( "include"         FILES ${INCLUDE} )
SOURCE_GROUP( "include\\alsa"   FILES ${alsa_INCLUDE} )
SOURCE_GROUP( "include\\config" FILES ${config_INCLUDE} )
SOURCE_GROUP( "include\\core"   FILES ${core_INCLUDE} )
SOURCE_GROUP( "include\\db"     FILES ${db_INCLUDE} )
SOURCE_GROUP( "include\\except" FILES ${except_INCLUDE} )
SOURCE_GROUP( "include\\stats"  FILES ${stats_INCLUDE} )
SOURCE_GROUP( "include\\util"   FILES ${util_INCLUDE} )

SOURCE_GROUP( "src"         FILES ${SOURCE} )
SOURCE_GROUP( "src\\alsa"   FILES ${alsa_SOURCE} )
SOURCE_GROUP( "src\\config" FILES ${config_SOURCE} )
SOURCE_GROUP( "src\\core"   FILES ${core_SOURCE} )
SOURCE_GROUP( "src\\db"     FILES ${db_SOURCE} )
SOURCE_GROUP( "src\\except" FILES ${except_SOURCE} )
SOURCE_GROUP( "src\\stats"  FILES ${stats_SOURCE} )
SOURCE_GROUP( "src\\util"   FILES ${util_SOURCE} )

ADD_LIBRARY( "${TARGET_NAME}"
             ${INCLUDE}        ${SOURCE}
             ${alsa_INCLUDE}   ${alsa_SOURCE}
             ${config_INCLUDE} ${config_SOURCE}
             ${core_INCLUDE}   ${core_SOURCE}
             ${db_INCLUDE}     ${db_SOURCE}
             ${except_INCLUDE} ${except_SOURCE}
             ${stats_INCLUDE}  ${stats_SOURCE}
             ${util_INCLUDE}   ${util_SOURCE} )

TARGET_BUILD_PCH( "${TARGET_NAME}"
                  "${TARGET_INCLUDE_DIR}/cgt-common.h"
                  "${TARGET_SOURCE_DIR}/cgt-compat.cpp" )
TARGET_LINK_LIBRARIES( "${TARGET_NAME}"
                       ${ALSA_LIBRARIES}
                       ${FFTW3_LIBRARIES}
                       "tinyxml" )
