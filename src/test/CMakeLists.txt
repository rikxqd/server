# test层cmake

# 设置变量
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/src/inc)
include_directories(${PROJECT_SOURCE_DIR}/third/tinyxml)

# 添加编译可执行目标文件及其依赖
#add_executable(server server/server.cpp)
#add_executable(client client/client.cpp)
#add_executable(mutilparam template/mutilparam.cpp)
#add_executable(template template/template.cpp)
#add_executable(typeoptest template/typeoptest.cpp)
add_executable(log log/log.cpp)
#add_executable(kmp kmp/kmp.cpp)
add_executable(thread_pool thread/thread_pool.cpp)
#add_executable(split str/split.cpp)
#add_executable(stream stream/stream.cpp)
add_executable(time time/time.cpp)
 

# 添加链接库
#target_link_libraries(server base xml)
#target_link_libraries(client base)
target_link_libraries(log base)
#target_link_libraries(mutilparam base)
#target_link_libraries(kmp base)
target_link_libraries(thread_pool pthread base)
#target_link_libraries(split base)
#target_link_libraries(stream base)
target_link_libraries(time base)