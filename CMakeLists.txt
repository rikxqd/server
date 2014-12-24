# 最上层cmake

# 支持的最低版本
cmake_minimum_required(VERSION 2.6)

# cmake过程输出
message(STATUS "GD_ENV = $ENV{GD_ENV}")

# 定义工程
project(TEST)

# 添加工程子目录
add_subdirectory(src/lib lib)
add_subdirectory(src/hello bin)

# 添加测试
add_test(mytest ${PROJECT_BINARY_DIR}/bin/main)
enable_testing()