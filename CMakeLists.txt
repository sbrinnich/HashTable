cmake_minimum_required(VERSION 3.6)
project(HashTable)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")

set(SOURCE_FILES main.cpp stock.h hashtable.h stock.cpp hashtable.cpp)
add_executable(HashTable ${SOURCE_FILES})