# Locate GLM library This module defines
#
# ::
#
#   GLM_FOUND          - if false, glm hasnt been found on your computer
#   GLM_INCLUDE_DIR    - location of glm headers
#

FIND_PATH(GLM_INCLUDE_DIR
    NAMES glm/glm.hpp
    PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /sw
    /opt/local
    /opt/csw
    /opt
	./lib/glm
    )

FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLM
    REQUIRED_VARS GLM_INCLUDE_DIR
    )
