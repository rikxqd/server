# hello层cmake

# 查找文件路径
find_path(myHeader hello.h)
if(myHeader)
      message(STATUS "This is SOURCE dir " ${myHeader})
      
      # 头文件引入
      include_directories(${myHeader})
endif()

# 执行命令
exec_program(ls ARGS "-a"  OUTPUT_VARIABLE LS_OUTPUT RETURN_VALUE LS_RVALUE)
if(NOT LS_RVALUE)
      message(STATUS "ls result:  " ${LS_OUTPUT})
endif(NOT LS_RVALUE)

# 添加宏
add_definitions($ENV{GD_ENV})

# 添加编译可执行目标文件及其依赖
add_executable(main main.cpp)

# 链接动态库
target_link_libraries(main ${TEST_BINARY_DIR}/lib/libhello.so)