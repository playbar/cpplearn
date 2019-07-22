cmake_minimum_required(VERSION 3.6)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(${CMAKE_CXX_COMPILER_ID})

add_subdirectory(llvm)
#add_subdirectory(gtest)
#add_subdirectory(drmemory)
add_subdirectory(algorithm)
#add_subdirectory(boost)
#add_subdirectory(demo)
#add_subdirectory(gperftools)
#add_subdirectory(dl)
#add_subdirectory(json)
#add_subdirectory(professional_cpp)
#add_subdirectory(readelf)
#add_subdirectory(regex)
#add_subdirectory(stl)
#add_subdirectory(spdlog)
#add_subdirectory(sqlitetest)
#add_subdirectory(template)
#add_subdirectory(thread)
add_subdirectory(tools)
#add_subdirectory(unique_resource)
#add_subdirectory(unity)
#add_subdirectory(variant)
#add_subdirectory(vld)

MESSAGE("make files end")




#target_link_libraries()