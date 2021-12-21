# FindLAGraph
# --------
#
# Find the native LAGRAPH includes and library.
#
# IMPORTED Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines :prop_tgt:`IMPORTED` target ``LAGRAPH::LAGRAPH``, if
# LAGRAPH has been found.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
#   LAGRAPH_INCLUDE_DIRS   - where to find LAGraph.h, etc.
#   LAGRAPH_LIBRARIES      - List of libraries when using LAGraph.
#   LAGRAPH_FOUND          - True if LAGraph found.
#
# Hints
# ^^^^^
#
# A user may set ``LAGRAPH_ROOT`` to a LAGraph installation root to tell this
# module where to look.


# NB: this is built around assumptions about one particular LAGraph
# installation. As other installations become available changes to
# this will likely be required.

# "Include" for a well known installation with unconventional naming.
find_path(
  LAGRAPH_INCLUDE_DIR
  NAMES LAGraph.h
  PATHS ${LAGRAPH_ROOT}
  PATH_SUFFIXES include Include
  )

# "build" for a well known installation with unconventional naming.
find_library(
  LAGRAPH_LIBRARY
  NAMES lagraph_static
  PATHS ${LAGRAPH_ROOT}
  PATH_SUFFIXES lib lib64
  )

find_library(
  LAGRAPHX_LIBRARY
  NAMES lagraphx_static
  PATHS ${LAGRAPH_ROOT}
  PATH_SUFFIXES lib lib64
  )

# get version of .so using REALPATH
get_filename_component(LAGRAPH_LIBRARY ${LAGRAPH_LIBRARY} REALPATH)
get_filename_component(LAGRAPHX_LIBRARY ${LAGRAPHX_LIBRARY} REALPATH)
# string(
#   REGEX MATCH "[0-9]+.[0-9]+.[0-9]+"
#   LAGRAPH_VERSION
#   ${LAGRAPH_LIBRARY}
#   )
set(LAGRAPH_LIBRARIES ${LAGRAPHX_LIBRARY} ${LAGRAPH_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  LAGraph
  REQUIRED_VARS LAGRAPH_LIBRARIES LAGRAPH_INCLUDE_DIR
  # VERSION_VAR LAGRAPH_VERSION
  )

mark_as_advanced(
  LAGRAPH_INCLUDE_DIR
  LAGRAPH_LIBRARY
  LAGRAPH_LIBRARIES
  )
