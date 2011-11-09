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

################
# Dependencies #
################
FIND_PACKAGE( "ALSA" REQUIRED )
FIND_PACKAGE( "FFTW3" REQUIRED )

###########
# Targets #
###########
INCLUDE( "TargetBuildPCH" )

ADD_SUBDIRECTORY( "src/cgt-common" )
ADD_SUBDIRECTORY( "src/cgt-cli" )

###############
# CPack setup #
###############
SET( CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION_SUMMARY}" )
SET( CPACK_PACKAGE_VENDOR              "${PROJECT_VENDOR}" )
SET( CPACK_PACKAGE_VERSION             "${PROJECT_VERSION}" )

INCLUDE( "CPack" )
