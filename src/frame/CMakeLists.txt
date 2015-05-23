# lib层cmake

# 执行命令
#exec_program(ls ARGS "-a"  OUTPUT_VARIABLE LS_OUTPUT RETURN_VALUE LS_RVALUE)
#if(NOT LS_RVALUE)
#      message(STATUS "ls result:  " ${LS_OUTPUT})
#endif(NOT LS_RVALUE)

# 设置包含目录
include_directories(${PROJECT_SOURCE_DIR}/src/base)
include_directories(${PROJECT_SOURCE_DIR}/src/frame)

# 设置变量
set(LIBFRAME_SRC 
	net/network.cpp
	net/sock_func.cpp
	net/endpoint.cpp
	net/address.cpp
	net/net_handle.cpp
	server/server.cpp
	)
#aux_source_directory(process LIBBASE_SRC)
#aux_source_directory(net LIBBASE_SRC)

# 重设变量
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 添加动态库编译目标文件及其依赖文件
add_library(frame SHARED ${LIBFRAME_SRC})
# 静态库 add_library(base STATIC ${LIBBASE_SRC})