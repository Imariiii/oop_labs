cmake_minimum_required(VERSION 3.10)
project(lab_7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)

add_library(lab_7_lib ${SOURCES})
add_executable(${CMAKE_PROJECT_NAME}.exe main.cpp)
add_executable(test.exe ${TEST_SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}.exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)
target_include_directories(test.exe PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(test.exe PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest gtest_main)

add_test(NAME BASIC COMMAND test)
