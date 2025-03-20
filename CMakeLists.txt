cmake_minimum_required(VERSION 3.10)
project(LocalBigtable)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(LocalBigtable src/main.cpp src/bigtable.cpp)
