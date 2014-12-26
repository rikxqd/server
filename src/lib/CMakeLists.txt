# lib层cmake

# 设置变量
set(LIBHELLO_SRC hello.cpp)

# 重设变量
set(LIBRARY_OUTPUT_PATH ${SERVER_BINARY_DIR}/lib)

# 添加动态库编译目标文件及其依赖文件
add_library(hello SHARED ${LIBHELLO_SRC})
# 静态库 add_library(hello1 STATIC ${LIBHELLO_SRC})