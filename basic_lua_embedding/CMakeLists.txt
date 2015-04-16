cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project (basic_lua_embedding)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${PROJECT_SOURCE_DIR}/cmake
  )

find_package(Lua REQUIRED)

include_directories (
  ${LUA_INCLUDE_DIRS}
  )

add_executable(basic_lua_embedding main.cpp)

target_link_libraries(basic_lua_embedding ${LUA_LIBRARIES} )