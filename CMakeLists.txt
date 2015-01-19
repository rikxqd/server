# 最上层cmake

# 支持的最低版本
cmake_minimum_required(VERSION 2.6)

# cmake过程输出
message(STATUS "WS_PATH = $ENV{WS_PATH}")

# 定义工程
project(SERVER)

if(UNIX)
      add_definitions(-DUNIX)
endif(UNIX)

set(CMAKE_BUILD_TYPE "Debug")

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable")
else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

message("Build Type:" ${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS})


# 添加工程子目录
add_subdirectory(src/inc lib/base)
add_subdirectory(src/frame lib/frame)
add_subdirectory(src/test bin)

# 添加测试
#add_test(mytest ${PROJECT_BINARY_DIR}/bin/main)
#enable_testing()