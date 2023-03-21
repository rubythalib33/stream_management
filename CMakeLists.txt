cmake_minimum_required(VERSION 3.5)
project(opencv_example)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(main main.cpp)

target_link_libraries(main ${OpenCV_LIBS})
