# lua层cmake

set(CMAKE_C_FLAGS " -std=gnu99 -O2 -Wall -Wextra -DLUA_COMPAT_5_2 -DLUA_USE_LINUX")

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

# 编译liblua静态库
add_library(liblua STATIC ${LIBLUA_SRC})
set_target_properties(liblua PROPERTIES OUTPUT_NAME "lua")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/lua)

# 编译lua可执行文件
add_executable(lua lua.c)
target_link_libraries(lua liblua)
if(UNIX)
	target_link_libraries(lua m dl readline)
endif()
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/lua)

# 编译luac可执行文件
add_executable(luac luac.c)
target_link_libraries(luac liblua)
if(UNIX)
	target_link_libraries(luac m dl readline)
endif()
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/lua)
