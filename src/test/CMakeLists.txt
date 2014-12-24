# test层cmake

# 设置变量
set(EXECUTABLE_OUTPUT_PATH ${TEST_BINARY_DIR}/bin)

# 添加编译可执行目标文件及其依赖
add_executable(test main.cpp)