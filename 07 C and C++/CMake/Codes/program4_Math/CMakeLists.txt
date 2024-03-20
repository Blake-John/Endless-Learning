cmake_minimum_required (VERSION 3.10)
project (HELLO_WORLD)

add_subdirectory (MathFunctions)

add_executable (main main.cpp)

target_link_libraries (main mathfunc)
