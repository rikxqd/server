# xml层cmake

# 设置变量
set(LIBXML_SRC 
	tinystr.cpp
	tinyxml.cpp
	tinyxmlerror.cpp
	tinyxmlparser.cpp
	)
	
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")


# 添加动态库编译目标文件及其依赖文件
add_library(libxml STATIC ${LIBXML_SRC})
set_target_properties(libxml PROPERTIES OUTPUT_NAME "xml")