cmake_minimum_required(VERSION 4.1)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        pairContainer.h
        Header.cpp
        Header.h
)
configure_file(iot-shard.txt ${CMAKE_BINARY_DIR}/iot-shard.txt COPYONLY)