cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_C_COMPILER "clang")
  set(CMAKE_CXX_COMPILER "clang++")
endif()

project(ray_tracing)

find_package(Eigen3 3.4 REQUIRED NO_MODULE)
find_package(OpenMP)

add_subdirectory(src)
