add_library(detectfunc src/detectfunc.cpp)

target_link_libraries(detectfunc mathfunc)

find_package(OpenCV REQUIRED)

target_include_directories(detectfunc PUBLIC include)
target_include_directories(detectfunc PUBLIC ${OpenCV_INCLUDE_DIRS})

target_link_libraries(detectfunc ${OpenCV_LIBS})