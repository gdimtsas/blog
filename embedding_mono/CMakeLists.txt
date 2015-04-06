cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project (embedding_mono)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${PROJECT_SOURCE_DIR}/cmake
  )

find_package(Mono REQUIRED)

include_directories (
  ${MONO_INCLUDE_DIRS}
  )

add_executable(embedding_mono main.cpp)

target_link_libraries(embedding_mono ${MONO_LIBRARIES} )