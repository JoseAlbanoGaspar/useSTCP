cmake_minimum_required(VERSION 3.20)
project(STCPProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(STCPProject main.cpp codigo/Company.cpp codigo/Company.h codigo/disjointSets.h codigo/graph.h codigo/graph.cpp
        codigo/GraphMaker.cpp codigo/GraphMaker.h codigo/minHeap.h dataset codigo/GraphLine.cpp codigo/GraphLine.h)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dataset
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
