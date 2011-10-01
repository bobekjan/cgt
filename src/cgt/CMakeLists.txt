#
# Console Guitar Tuner (CGT)
# Copyright (c) 2011 by Bloody.Rabbit
#
# Author: Bloody.Rabbit
#

##############
# Initialize #
##############
SET( TARGET_NAME        "cgt" )
SET( TARGET_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/${TARGET_NAME}" )
SET( TARGET_SOURCE_DIR  "${PROJECT_SOURCE_DIR}/src/${TARGET_NAME}" )

#########
# Files #
#########
SET( INCLUDE
     "${TARGET_INCLUDE_DIR}/cgt.h" )
SET( SOURCE
     "${TARGET_SOURCE_DIR}/cgt.cpp" )

SET( alsa_INCLUDE
     "${TARGET_INCLUDE_DIR}/alsa/Error.h"
     "${TARGET_INCLUDE_DIR}/alsa/Error.inl"
     "${TARGET_INCLUDE_DIR}/alsa/Pcm.h"
     "${TARGET_INCLUDE_DIR}/alsa/Pcm.inl" )
SET( alsa_SOURCE
     "" )

########################
# Setup the executable #
########################
INCLUDE_DIRECTORIES( ${ALSA_INCLUDE_DIRS}
                     "${TARGET_INCLUDE_DIR}" )

SOURCE_GROUP( "include"       FILES ${INCLUDE} )
SOURCE_GROUP( "include\\alsa" FILES ${alsa_INCLUDE} )

SOURCE_GROUP( "src"       FILES ${SOURCE} )
SOURCE_GROUP( "src\\alsa" FILES ${alsa_SOURCE} )

ADD_EXECUTABLE( "${TARGET_NAME}"
                ${INCLUDE}      ${SOURCE}
                ${alsa_INCLUDE} ${alsa_SOURCE} )

TARGET_BUILD_PCH( "${TARGET_NAME}"
                  "${TARGET_INCLUDE_DIR}/cgt.h"
                  "${TARGET_SOURCE_DIR}/cgt.cpp" )
TARGET_LINK_LIBRARIES( "${TARGET_NAME}"
                       ${ALSA_LIBRARIES} )

######################
# Export directories #
######################
SET( ${TARGET_NAME}_INCLUDE_DIR "${TARGET_INCLUDE_DIR}" PARENT_SCOPE )
