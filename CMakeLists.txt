cmake_minimum_required(VERSION 3.8)
project(muted VERSION 0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)