# lib层cmake

# 执行命令
#exec_program(ls ARGS "-a"  OUTPUT_VARIABLE LS_OUTPUT RETURN_VALUE LS_RVALUE)
#if(NOT LS_RVALUE)
#      message(STATUS "ls result:  " ${LS_OUTPUT})
#endif(NOT LS_RVALUE)

# 设置变量
set(LIBBASE_SRC 
	net/warp_socket.cpp 
	net/address.cpp
	process/process.cpp
	thread/thread_pool.cpp
	thread/thread_worker.cpp
	thread/thread_task.cpp
	log/log.cpp
	log/source_file.cpp
	global.cpp
	stream/stream.cpp
	string/str_fun.cpp
	)
#aux_source_directory(process LIBBASE_SRC)
#aux_source_directory(net LIBBASE_SRC)

# 重设变量
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 设置包含目录
include_directories(${PROJECT_SOURCE_DIR}/src/inc)

# 添加动态库编译目标文件及其依赖文件
add_library(base SHARED ${LIBBASE_SRC})
target_link_libraries(base pthread)
# 静态库 add_library(base STATIC ${LIBBASE_SRC})