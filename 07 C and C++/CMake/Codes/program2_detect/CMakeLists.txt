cmake_minimum_required(VERSION 3.0)
project(DETECT)

set(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV REQUIRED)

add_subdirectory(mathfunc)
add_subdirectory(detectfunc)

add_executable(main main.cpp)

target_include_directories(main PUBLIC ${OpenCV_INCLUDE_DIRS})

target_link_libraries(main ${OpenCV_LIBS})
target_link_libraries(main mathfunc)
target_link_libraries(main detectfunc)