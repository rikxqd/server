# test层cmake

# 设置变量
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

message(STATUS "include dir = ${PROJECT_SOURCE_DIR}/src/inc")
include_directories(${PROJECT_SOURCE_DIR}/src/inc)

# 添加编译可执行目标文件及其依赖
add_executable(test main.cpp)

# 添加链接库
target_link_libraries(test base)