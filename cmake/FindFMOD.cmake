# Locate FMOD library This module defines
#
# ::
#
#   FMOD_FOUND          - if false, fmod hasnt been found on your computer
#   FMOD_LIBRARY        - location of fmod library
#   FMOD_INCLUDE_DIR    - location of fmod headers
#

FIND_PATH(FMOD_INCLUDE_DIR
    NAMES fmod/fmod.h
   HINTS
      ENV FMOD_DIR
    PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /sw
    /opt/local
    /opt/csw
    /opt
	./lib/fmod_windows/inc
    )

FIND_LIBRARY(FMOD_LIBRARY
    NAMES fmodL
    HINTS
      ENV FMOD_DIR
    PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /sw
    /opt/local
    /opt/csw
    /opt
	./lib/fmod_windows/lib
    )

FIND_PACKAGE_HANDLE_STANDARD_ARGS(FMOD
    REQUIRED_VARS FMOD_LIBRARY FMOD_INCLUDE_DIR
    )
