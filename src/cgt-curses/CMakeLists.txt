#
# Console Guitar Tuner (CGT)
# Copyright (c) 2011 by Bloody.Rabbit
#
# Author: Bloody.Rabbit
#

##############
# Initialize #
##############
SET( TARGET_NAME        "cgt-curses" )
SET( TARGET_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/${TARGET_NAME}" )
SET( TARGET_SOURCE_DIR  "${PROJECT_SOURCE_DIR}/src/${TARGET_NAME}" )

SET( TARGET_INCLUDE_DIRS
     ${cgt-common_INCLUDE_DIRS}
     "${TARGET_INCLUDE_DIR}" )

# Export the include directories
SET( ${TARGET_NAME}_INCLUDE_DIRS ${TARGET_INCLUDE_DIRS} PARENT_SCOPE )

#########
# Files #
#########
SET( INCLUDE
     "${TARGET_INCLUDE_DIR}/cgt-curses.h" )
SET( SOURCE
     "${TARGET_SOURCE_DIR}/cgt-curses.cpp" )

########################
# Setup the executable #
########################
INCLUDE_DIRECTORIES( ${TARGET_INCLUDE_DIRS} )

SOURCE_GROUP( "include" FILES ${INCLUDE} )
SOURCE_GROUP( "src"     FILES ${SOURCE} )

ADD_EXECUTABLE( "${TARGET_NAME}"
                ${INCLUDE} ${SOURCE} )

TARGET_BUILD_PCH( "${TARGET_NAME}"
                  "${TARGET_INCLUDE_DIR}/cgt-curses.h"
                  "${TARGET_SOURCE_DIR}/cgt-curses.cpp" )
TARGET_LINK_LIBRARIES( "${TARGET_NAME}"
                       "cgt-common" )
