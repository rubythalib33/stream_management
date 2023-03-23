cmake_minimum_required(VERSION 3.5)
project(opencv_example)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

# Add the include directory to the include path
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the OpenCV include directory to the include path
include_directories(${OpenCV_INCLUDE_DIRS})

# Add the utility source files to the project
add_library(base64 src/utility/base64.cpp)

# Add the main executable
add_executable(main main.cpp)

# Link the main executable with OpenCV and the utility library
target_link_libraries(main ${OpenCV_LIBS} base64)
