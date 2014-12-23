find_path(myHeader hello.h)
if(myHeader)
      message(STATUS "This is SOURCE dir " ${myHeader})
      include_directories(${myHeader})
endif()

exec_program(ls ARGS "-a"  OUTPUT_VARIABLE LS_OUTPUT RETURN_VALUE LS_RVALUE)
if(NOT LS_RVALUE)
      MESSAGE(STATUS "ls result:  " ${LS_OUTPUT})
endif(NOT LS_RVALUE)

add_definitions($ENV{GD_ENV})

add_executable(main main.cpp)

target_link_libraries(main ${TEST_BINARY_DIR}/lib/libhello.so)