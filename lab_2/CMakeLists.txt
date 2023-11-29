cmake_minimum_required(VERSION 3.10)
project(lab_2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab_2 main.cpp ../src/decarray.cpp)
add_executable(tests ../test/tests.cpp ../src/decarray.cpp)

find_package(GTest REQUIRED)
target_link_libraries(tests GTest::GTest GTest::Main)

target_include_directories(lab_2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})