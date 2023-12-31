cmake_minimum_required(VERSION 3.10)
project(SWAP)

include_directories(include)
# 将头文件的所在的路径添加到搜索路径，这样就可以引用目标头文件

add_executable(main main.cpp src/swap.cpp)
