add_library(mathfunc src/mathfunc.cpp)

find_package(OpenCV REQUIRED)

target_include_directories(mathfunc PUBLIC include)
target_include_directories(mathfunc PUBLIC ${OpenCV_INCLUDE_DIRS})

target_link_libraries(mathfunc ${OpenCV_LIBS})
