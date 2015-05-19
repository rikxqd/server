# lib层cmake

# 执行命令
#exec_program(ls ARGS "-a"  OUTPUT_VARIABLE LS_OUTPUT RETURN_VALUE LS_RVALUE)
#if(NOT LS_RVALUE)
#      message(STATUS "ls result:  " ${LS_OUTPUT})
#endif(NOT LS_RVALUE)

# 设置变量
set(LIBBASE_SRC 
	net/sock_func.cpp 
	net/address.cpp
	process/process.cpp
	thread/thread_pool.cpp
	thread/thread_worker.cpp
	thread/thread_lock.cpp
	thread/thread_func.cpp
	log/log.cpp
	log/source_file.cpp
	log/log_stream.cpp
	global.cpp
	stream/stream.cpp
	str/str_func.cpp
	time/time.cpp
	time/time_func.cpp
	time/timer.cpp
	time/timer_manager.cpp
	utility/math.cpp
	utility/ref_counter.cpp
	epoll/epoll.cpp
	)
#aux_source_directory(process LIBBASE_SRC)
#aux_source_directory(net LIBBASE_SRC)

# 重设变量
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 设置包含目录
include_directories(${PROJECT_SOURCE_DIR}/src/base)

# 添加动态库编译目标文件及其依赖文件
#add_library(base SHARED ${LIBBASE_SRC})
add_library(base STATIC ${LIBBASE_SRC})
target_link_libraries(base pthread)