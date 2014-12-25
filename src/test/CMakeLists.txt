# test层cmake

# 设置变量
set(EXECUTABLE_OUTPUT_PATH ${TEST_BINARY_DIR}/bin)

message(STATUS "include dir = ${PROJECT_SOURCE_DIR}/src/inc")
include_directories(${PROJECT_SOURCE_DIR}/src/inc)

# 添加编译可执行目标文件及其依赖
add_executable(main main.cpp)