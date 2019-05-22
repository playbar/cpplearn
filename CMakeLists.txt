cmake_minimum_required(VERSION 3.6)
project(cpplearn LANGUAGES CXX C)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fpermissive -fvisibility=hidden -Wall -std=c++17" )

set(CMAKE_CXX_STANDARD 14)

message(${CMAKE_CXX_COMPILER_ID})

#add_subdirectory(boost)
#add_subdirectory(gtest)
add_subdirectory(demo)
add_subdirectory(gperftools)
#add_subdirectory(dl)
#add_subdirectory(json)
add_subdirectory(json11)
#add_subdirectory(llvm)
#add_subdirectory(readelf)
#add_subdirectory(regex)
#add_subdirectory(stl)
add_subdirectory(stl_source)
#add_subdirectory(spdlog)
#add_subdirectory(sqlitetest)
#add_subdirectory(template)
#add_subdirectory(thread)
add_subdirectory(tlsf)
#add_subdirectory(unique_resource)
#add_subdirectory(unity)
#add_subdirectory(variant)
#add_subdirectory(vld)

MESSAGE("make files end")




#target_link_libraries()