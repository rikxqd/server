cmake_minimum_required(VERSION 2.6)

message(STATUS "GD_ENV = $ENV{GD_ENV}")

project(TEST)

add_subdirectory(src/lib lib)
add_subdirectory(src/hello bin)

add_test(mytest ${PROJECT_BINARY_DIR}/bin/main)
enable_testing()