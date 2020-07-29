# demo

cmake_minimum_required(VERSION 3.6)
project(algorithm LANGUAGES CXX C)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fpermissive -fvisibility=hidden -std=c++17" )
set(CMAKE_CXX_STANDARD 17)

add_definitions(-Werror=return-type)

add_subdirectory(grass_rtree)
add_subdirectory(rtree)

add_executable(lrbteetest
        lrbtree.c
        lrbtreetest.c)

add_executable(RBTreeTest
        RBTree.cpp
        RBTreeTest.cpp)

add_executable(algorithm_test
        test1.cpp
)

add_executable(quick_sort
        quick_sort.cpp)