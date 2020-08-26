CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

#项目名称
PROJECT(threadpool)

#查找目录下的所有源文件
AUX_SOURCE_DIRECTORY(src SOURCE_LIST)
#设置编译器（可选的有gcc，g++)
SET(CMAKE_CXX_COMPILER "g++")
# 设置编译选项
# 允许c++11标准、O3优化、多线程。match选项可避免一些cpu上的问题
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3 -pthread" )
#设定存放编译出来的库文件的目录
SET( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#并且把该目录设为连接目录
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/lib)
#设定可执行二进制文件的目录
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#设定头文件目录
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/inc)

#添加可执行文件
ADD_EXECUTABLE(threadpool ${SOURCE_LIST})
