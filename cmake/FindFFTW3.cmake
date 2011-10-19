# - Find FFTW3
# Find the native FFTW3 includes and library
#
#   FFTW3_FOUND        - True if FFTW3 found.
#   FFTW3_INCLUDE_DIRS - where to find fftw3.h, etc.
#   FFTW3_LIBRARIES    - List of libraries when using FFTW3.
#

FIND_PATH( FFTW3_INCLUDE_DIRS "fftw3.h" )

FIND_LIBRARY( FFTW3_LIBRARIES NAMES "fftw3" )

# handle the QUIETLY and REQUIRED arguments and set FFTW3_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE( "FindPackageHandleStandardArgs" )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( "FFTW3" DEFAULT_MSG FFTW3_INCLUDE_DIRS FFTW3_LIBRARIES )

MARK_AS_ADVANCED( FFTW3_INCLUDE_DIRS FFTW3_LIBRARIES )
