cmake_minimum_required(VERSION 3.8)
project(ALGRTM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c mccalc.c mccalc.h)

add_executable(ALGRTM ${SOURCE_FILES})
target_link_libraries(ALGRTM m)