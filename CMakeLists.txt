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

# 添加工程子目录
add_subdirectory(src/inc lib)
add_subdirectory(src/test bin)

# 添加测试
#add_test(mytest ${PROJECT_BINARY_DIR}/bin/main)
#enable_testing()