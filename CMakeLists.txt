cmake_minimum_required(VERSION 2.8)

project(ransac)

file(GLOB SRC_FILES src/*.cpp)

include_directories(include)

add_executable(ransac ${SRC_FILES})