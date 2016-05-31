# lua层cmake

# 设置变量
set(LIBLUA_SRC 
	lapi.c
	lcode.c
	lctype.c
	ldebug.c
	ldo.c
	ldump.c
	lfunc.c
	lgc.c
	llex.c
	lmem.c
	lobject.c
	lopcodes.c
	lparser.c
	lstate.c
	lstring.c
	ltable.c
	ltm.c
	lundump.c
	lvm.c
	lzio.c
	lauxlib.c
	lbaselib.c
	lbitlib.c
	lcorolib.c
	ldblib.c
	liolib.c
	lmathlib.c
	loslib.c
	lstrlib.c
	ltablib.c
	lutf8lib.c
	loadlib.c
	linit.c
	)
	
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lm -Wl,-E -ldl")	
#set(gcc -fPIC -o test test.c ../liblua/src/liblua.a -lm -Wl,-E -ldl)
message("Build Type:" ${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS})
# 添加动态库编译目标文件及其依赖文件
add_library(lua STATIC ${LIBLUA_SRC})

#cmake_minimum_required (VERSION 2.8)
#project(lua)
#
#if(WIN32)
#	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
#endif()
#
#add_library(lualib
#			STATIC
#			lapi.c
#			lcode.c
#			lctype.c
#			ldebug.c
#			ldo.c
#			ldump.c
#			lfunc.c
#			lgc.c
#			llex.c
#			lmem.c
#			lobject.c
#			lopcodes.c
#			lparser.c
#			lstate.c
#			lstring.c
#			ltable.c
#			ltm.c
#			lundump.c
#			lvm.c
#			lzio.c
#			lauxlib.c
#			lbaselib.c
#			lbitlib.c
#			lcorolib.c
#			ldblib.c
#			liolib.c
#			lmathlib.c
#			loslib.c
#			lstrlib.c
#			ltablib.c
#			lutf8lib.c
#			loadlib.c
#			linit.c)
#set_target_properties(lualib PROPERTIES OUTPUT_NAME "lua")