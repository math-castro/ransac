#cmake version 
cmake_minimum_required(VERSION 2.8)
# CMake
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
# project declarations
project(ransac)
project(test)
# C++ and Compiler
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# add_compile_options(-Wall -Wextra)
add_compile_options(-Wall)
# add_compile_options(-Wreturn-type)
# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
# Eigen
# set(Eigen3_DIR "~/opt/include/eigen3/Eigen")
find_package(Eigen3 3.3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
# message(${EIGEN3_INCLUDE_DIR})
# source files
file(GLOB_RECURSE SRC_FILES "src/*.cpp")
list(FILTER SRC_FILES EXCLUDE REGEX "main.cpp")
list(FILTER SRC_FILES EXCLUDE REGEX "test.cpp")
# message(${SRC_FILES})
# message("${SRC_FILES}")
include_directories(include)
# ransac
add_executable(ransac ${SRC_FILES} "src/main.cpp")
target_link_libraries(ransac ${OpenCV_LIBS})
# test
add_executable(test ${SRC_FILES} "src/test/test.cpp")
target_link_libraries(test ${OpenCV_LIBS})
