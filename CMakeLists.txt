cmake_minimum_required(VERSION 3.6)
project(Janus)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp graph.cpp graph.h vertex.cpp vertex.h edgeinfo.cpp edgeinfo.h)
add_executable(Janus ${SOURCE_FILES} graph.cpp graph.h)