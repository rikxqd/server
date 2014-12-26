# lib层cmake

# 设置变量
set(LIBBASE_SRC net/warp_socket.cpp)

# 重设变量
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/src/inc)

# 添加动态库编译目标文件及其依赖文件
add_library(base SHARED ${LIBBASE_SRC})
# 静态库 add_library(base STATIC ${LIBBASE_SRC})