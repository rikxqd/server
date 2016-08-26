# lib层cmake

# 执行命令
#exec_program(ls ARGS "-a"  OUTPUT_VARIABLE LS_OUTPUT RETURN_VALUE LS_RVALUE)
#if(NOT LS_RVALUE)
#      message(STATUS "ls result:  " ${LS_OUTPUT})
#endif(NOT LS_RVALUE)

# 设置变量
set(LIBBASE_SRC
	global.cpp
	process/process.cpp
	thread/thread_pool.cpp
	thread/thread_worker.cpp
	thread/thread_lock.cpp
	thread/thread_api.cpp
	stream/stream.cpp
	log/log.cpp
	log/source_file.cpp
	log/log_stream.cpp
	time/time.cpp
	time/timer.cpp
	time/timer_manager.cpp
	utility/math.cpp
	utility/ref_counter.cpp
	utility/common.cpp
	utility/collision/common.cpp
	utility/collision/collision_math.cpp
	net/network.cpp
	net/net_api.cpp
	net/endpoint.cpp
	net/address.cpp
	net/net_handle.cpp
	net/event_poller.cpp
	net/select_poller.cpp
	net/acceptor.cpp
	framework/server_app.cpp
	)
#aux_source_directory(process LIBBASE_SRC)
#aux_source_directory(net LIBBASE_SRC)

# 重设变量
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 设置包含目录
include_directories(${PROJECT_SOURCE_DIR}/src/base)

# 添加动态库编译目标文件及其依赖文件
#add_library(base SHARED ${LIBBASE_SRC})
add_library(libbase STATIC ${LIBBASE_SRC})
target_link_libraries(libbase pthread)
set_target_properties(libbase PROPERTIES OUTPUT_NAME "base")