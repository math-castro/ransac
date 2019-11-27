#cmake version 
cmake_minimum_required(VERSION 2.8)
# sets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
# source files
file(GLOB SRC_FILES src/*.cpp)
include_directories(include)
# project
project(ransac)
add_executable(ransac ${SRC_FILES})
target_link_libraries(ransac ${OpenCV_LIBS})
