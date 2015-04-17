# Locate Lua library
# This module defines
#  LUA_FOUND, if false, do not try to link to Lua
#  LUA_LIBRARIES
#  LUA_INCLUDE_DIRS, where to find lua.h
#
# Note that the expected include convention is
#  #include "lua.h"
# and not
#  #include <lua/lua.h>
# This is because, the lua location is not standardized and may exist
# in locations other than lua/

include(LibFindMacros)

set(LUA_ROOT $ENV{LUA_ROOT})

find_path(LUA_INCLUDE_DIR
  NAMES lua.h
  HINTS
  ${LUA_ROOT}
  PATH_SUFFIXES include/lua52 include/lua5.2 include/lua include
  PATHS
  /usr/local
  /usr
  )

find_library(LUA_LIB_DEBUG
  NAMES lua_d.lib lua52_d.lib liblua_d.so liblua5.2_d.so
  PATHS
  ${LUA_ROOT}/lib
  /usr/lib/x86_64-linux-gnu/
  )

find_library(LUA_LIB_RELEASE
  NAMES lua.lib lua52.lib liblua.so liblua5.2.so
  PATHS
  ${LUA_ROOT}/lib
  /usr/lib/x86_64-linux-gnu/
  )

SET(LUA_LIB optimized ${LUA_LIB_RELEASE} debug ${LUA_LIB_DEBUG})

set(LUA_PROCESS_INCLUDES LUA_INCLUDE_DIR)
set(LUA_PROCESS_LIBS LUA_LIB)

libfind_process(LUA)