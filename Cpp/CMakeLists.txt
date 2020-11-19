cmake_minimum_required(VERSION 3.5) 
project(GildedRose) 
include_directories(
  $ENV{GTEST_HOME}/googlemock/include 
  $ENV{GTEST_HOME}/googletest/include
  ./src
  ./test
)

link_directories(
  $ENV{GTEST_HOME}/mybuild/googlemock 
  $ENV{GTEST_HOME}/mybuild/googlemock/gtest
)

add_definitions(-std=c++14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall")

# GCov
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
if(CMAKE_COMPILER_IS_GNUCXX)
  include(CodeCoverage)
  APPEND_COVERAGE_COMPILER_FLAGS()
  setup_target_for_coverage(
    NAME ${PROJECT_NAME}_coverage 
    EXECUTABLE ${PROJECT_NAME}_Test 
    DEPENDENCIES ${PROJECT_NAME}
  )
endif()

set(lib_sources
  src/GildedRose.cpp
)

set(sources
  test/GildedRose_Test.cpp
)

add_executable(${PROJECT_NAME}_Test ${sources})
add_library(${PROJECT_NAME} ${lib_sources})

target_link_libraries(${PROJECT_NAME}_Test pthread)
target_link_libraries(${PROJECT_NAME}_Test gmock)
target_link_libraries(${PROJECT_NAME}_Test gtest)
target_link_libraries(${PROJECT_NAME}_Test ${PROJECT_NAME})

