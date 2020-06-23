cmake_minimum_required(VERSION 3.4)

project(cpplearn LANGUAGES CXX C)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fpermissive -fvisibility=hidden -Wall -std=c++17" )
#set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-narrowing -fexceptions")

message(${CMAKE_CXX_COMPILER_ID})

#add_subdirectory(llvm)
#add_subdirectory(gtest)
#add_subdirectory(drmemory)
#add_subdirectory(algorithm)
#add_subdirectory(boost)
#add_subdirectory(demo)
#add_subdirectory(gperftools)
#add_subdirectory(jemalloc)
#add_subdirectory(dl)
#add_subdirectory(json)
#add_subdirectory(professional_cpp)
#add_subdirectory(readelf)
#add_subdirectory(regex)
#add_subdirectory(stl)
#add_subdirectory(spdlog)
#add_subdirectory(sqlitetest)
#add_subdirectory(template)
add_subdirectory(thread)
#add_subdirectory(tools)
#add_subdirectory(unique_resource)
#add_subdirectory(unity)
#add_subdirectory(valgrind)
#add_subdirectory(variant)
#add_subdirectory(vld)

MESSAGE("make files end")




#target_link_libraries()