#
# Console Guitar Tuner (CGT)
# Copyright (c) 2011 by Bloody.Rabbit
#
# Author: Bloody.Rabbit
#

###############
# CMake setup #
###############
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 FATAL_ERROR )

PROJECT( "cgt" )
SET( PROJECT_DESCRIPTION_SUMMARY "A console-based guitar tuner" )
SET( PROJECT_VENDOR              "Bloody.Rabbit" )
SET( PROJECT_VERSION             "0.0.0" )

SET( CMAKE_MODULE_PATH
     "${PROJECT_SOURCE_DIR}/cmake"
     "${CMAKE_MODULE_PATH}" )

##############
# Pre-target #
##############
INCLUDE( "CheckIncludeFile" )
INCLUDE( "TargetBuildPCH" )

ADD_DEFINITIONS( "-DHAVE_CONFIG_H=1" )
INCLUDE_DIRECTORIES( "${PROJECT_BINARY_DIR}" )

###########
# Targets #
###########
ADD_SUBDIRECTORY( "doc" )
ADD_SUBDIRECTORY( "src/cgt-common" )
ADD_SUBDIRECTORY( "src/cgt-curses" )

###############
# Post-target #
###############
CONFIGURE_FILE( "config.h.in" "config.h"
                ESCAPE_QUOTES )

###############
# CPack setup #
###############
SET( CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION_SUMMARY}" )
SET( CPACK_PACKAGE_VENDOR              "${PROJECT_VENDOR}" )
SET( CPACK_PACKAGE_VERSION             "${PROJECT_VERSION}" )

INCLUDE( "CPack" )
