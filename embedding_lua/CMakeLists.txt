cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project (embedding_lua)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${PROJECT_SOURCE_DIR}/cmake
  )

find_package(Lua REQUIRED)

include_directories (
  ${LUA_INCLUDE_DIRS}
  )

add_executable(embedding_lua main.cpp EngineLua.cpp Engine.h Entity.h Component.h TransformationComponent.h)

target_link_libraries(embedding_lua ${LUA_LIBRARIES} )