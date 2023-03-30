cmake_minimum_required(VERSION 3.5)
project(stream_management)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

add_library(base64 ${CMAKE_SOURCE_DIR}/src/utility/base64.cpp)

add_library(camera ${CMAKE_SOURCE_DIR}/src/camera/camera.cpp)

add_library(stream_management ${CMAKE_SOURCE_DIR}/src/camera/stream_management.cpp)

add_executable(main ${CMAKE_SOURCE_DIR}/src/main.cpp)

target_link_libraries(main 
    ${OpenCV_LIBS}
    ${Boost_LIBRARIES}
    stream_management
    camera
    base64
    pthread
)
