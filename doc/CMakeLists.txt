#
# CMake build system file for EVEmu.
#
# Author: Bloody.Rabbit
#

################
# Dependencies #
################
FIND_PACKAGE( "Doxygen" )

IF( NOT DOXYGEN_FOUND )
  MESSAGE( STATUS "WARNING: Generated documentation won't be available" )
  RETURN()
ENDIF( NOT DOXYGEN_FOUND )

#########
# Files #
#########
SET( DOXYGEN_TEMPLATE "Doxyfile.in" )
SET( DOXYGEN_INPUT    "Doxyfile" )
SET( DOXYGEN_OUTPUT   "html" )

CONFIGURE_FILE( "${DOXYGEN_TEMPLATE}"
                "${DOXYGEN_INPUT}"
                ESCAPE_QUOTES @ONLY )

########################
# Setup the generation #
########################
ADD_CUSTOM_COMMAND( OUTPUT ${DOXYGEN_OUTPUT}
                    COMMAND "${DOXYGEN_EXECUTABLE}" ARGS "${DOXYGEN_INPUT}"
                    DEPENDS "${DOXYGEN_INPUT}"
                    COMMENT "Generating documentation"
                    VERBATIM )

ADD_CUSTOM_TARGET( "doc" ALL
                   DEPENDS ${DOXYGEN_OUTPUT}
                   SOURCES "${DOXYGEN_TEMPLATE}" )

INSTALL( DIRECTORY ${DOXYGEN_OUTPUT}
         DESTINATION "doc/${PROJECT_NAME}-${PROJECT_VERSION}" )
