cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

if (APPLE)
  set(CMAKE_C_COMPILER "clang")
  set(CMAKE_CXX_COMPILER "clang++")
endif()

project(ray_tracing)

find_package(Eigen3 3.4 REQUIRED NO_MODULE)
find_package(OpenMP)

include_directories(include)
include_directories(include/core)
include_directories(include/Hittables)
include_directories(include/Materials)

add_subdirectory(src)
