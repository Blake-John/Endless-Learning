cmake_minimum_required(VERSION 3.10)
project(SOLIDERFIRE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -Wall")

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(my_cmake_exe main.cpp src/Gun.cpp src/Solider.cpp)