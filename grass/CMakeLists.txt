cmake_minimum_required(VERSION 3.4.1)

#boost_1_70_0

#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -fexceptions -frtti -fPIC HAVE_INT64_T=1")
add_definitions(-DHAVE_INT64_T=1)

#add_library(boost_test STATIC
#
#        )
#
#target_include_directories(boost_test PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}
#        ${CMAKE_CURRENT_SOURCE_DIR}/libs/test
#        )
#
######
#
#add_library(boost_all STATIC
#
#        )
#
#
#target_include_directories(boost_all PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}
#        ${CMAKE_CURRENT_SOURCE_DIR}/libs/filesystem/include
#        ${CMAKE_CURRENT_SOURCE_DIR}/libs/math/include_private
#        ${CMAKE_CURRENT_SOURCE_DIR}/libs/thread/include
#        )


###
add_executable(grass_rtree_test
        lib/vector/rtree/card.c
        lib/vector/rtree/index.c
        lib/vector/rtree/io.c
        lib/vector/rtree/node.c
        lib/vector/rtree/rect.c
        lib/vector/rtree/split.c
        lib/vector/rtree/test_suite/test_basics.c
        lib/vector/rtree/test_suite/test_main.c
        )
target_include_directories(grass_rtree_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/vector/rtree
        )
#target_link_libraries(grass_rtree_test
#        boost_test
#        boost_all)

