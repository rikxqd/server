# test层cmake

# 设置变量
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/src/inc)

# 添加编译可执行目标文件及其依赖
add_executable(server server.cpp)
add_executable(client client.cpp)

# 添加链接库
target_link_libraries(server base /mnt/hgfs/share/server/third/tinyxml/libxml.a)
target_link_libraries(client base)