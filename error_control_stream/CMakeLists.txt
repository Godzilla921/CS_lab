#	设定版本
CMAKE_MINIMUM_REQUIRED(VERSION 2.8) 
#	设定工程名
PROJECT(demo) 
#	设定编译器
SET(CMAKE_CXX_COMPILER "g++")  
#	设定可执行二进制文件的目录（最后生成的可执行文件放置的目录）
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#	设定链接目录
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
#	设定头文件目录
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
#	增加子文件夹，进入源代码文件夹继续构建
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/src)
