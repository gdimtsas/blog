cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project (mono_generics)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${PROJECT_SOURCE_DIR}/cmake
  )

find_package(Mono REQUIRED)

include_directories (
  ${MONO_INCLUDE_DIRS}
  )

add_executable(mono_generics main.cpp)

target_link_libraries(mono_generics ${MONO_LIBRARIES} )