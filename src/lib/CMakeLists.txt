set(LIBHELLO_SRC hello.cpp)
set(LIBRARY_OUTPUT_PATH ${TEST_BINARY_DIR}/lib)

add_library(hello SHARED ${LIBHELLO_SRC})
add_library(hello1 STATIC ${LIBHELLO_SRC})