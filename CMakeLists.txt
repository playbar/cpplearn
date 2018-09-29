cmake_minimum_required(VERSION 3.6)
project(cpplearn)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fpermissive -fvisibility=hidden -Wall -std=c++14" )

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(cnn)
add_subdirectory(crypto)
add_subdirectory(demo)
add_subdirectory(googletest)
add_subdirectory(json)
#add_subdirectory(json11)
#add_subdirectory(pb)
add_subdirectory(readelf)
add_subdirectory(regex)
add_subdirectory(sqlitetest)
add_subdirectory(src)
add_subdirectory(template)
add_subdirectory(thread)
add_subdirectory(unity)
add_subdirectory(variant)

MESSAGE("make files")

message(${CMAKE_CXX_COMPILER_ID})


set(SOURCE_DL  dl/dnn.cpp)
add_executable(dltest ${SOURCE_DL})

#unique_resource
set(unique_resource_file unique_resource/test1.cpp)
add_executable(unique_resourcetest ${unique_resource_file})

#target_link_libraries()