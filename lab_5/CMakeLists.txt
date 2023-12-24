cmake_minimum_required(VERSION 3.10)
project(lab_5)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(lab5 main.cpp include/allocator.h include/node.h include/queue.h)


target_include_directories(lab5 PRIVATE include)
set_target_properties(lab5 PROPERTIES OUTPUT_NAME "main")

add_executable(lab5_test test/test.cpp include/allocator.h include/node.h include/queue.h)


target_include_directories(lab5_test PRIVATE include)
set_target_properties(lab5_test PROPERTIES OUTPUT_NAME "test")
target_link_libraries(lab5_test ${GTEST_LIBRARIES})

enable_testing()
add_test(lab5_test lab5_test)