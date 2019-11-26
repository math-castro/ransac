cmake_minimum_required(VERSION 2.8)

find_package(OpenCV REQUIRED)

project(ransac)

file(GLOB SRC_FILES src/*.cpp)

include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ransac ${SRC_FILES})

target_link_libraries(ransac ${OpenCV_LIBS})
