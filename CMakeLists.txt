cmake_minimum_required(VERSION 3.6)
project(cpplearn)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fpermissive -fvisibility=hidden -Wall -std=c++14" )

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(cnn)
add_subdirectory(crypto)
add_subdirectory(json)
add_subdirectory(pb)
add_subdirectory(readelf)
add_subdirectory(regex)
add_subdirectory(sqlitetest)
add_subdirectory(unity)
add_subdirectory(variant)

set(SOURCE_FILES src/main.cpp src/CTest.cpp )
add_executable(CLionTest ${SOURCE_FILES})

MESSAGE("make files")

message(${CMAKE_CXX_COMPILER_ID})


set(SOURCE_FILES1 thread/main2.cpp src/CTest.cpp )
add_executable(CLionTest2 ${SOURCE_FILES1})

set(SOURCE_PARSESO parseso/ParseSo.cpp parseso/elf.h)
add_executable(ParseSo ${SOURCE_PARSESO})

set(SOURCE_PARSESO src/nth_element.cpp)
add_executable(nth_element ${SOURCE_PARSESO})


set(SOURCE_PARSESO demo/CppBase/map.cpp)
add_executable(CppBase ${SOURCE_PARSESO})

set(SOURCE_PARSESO demo/memtest/MemoryDetector.cpp)
add_executable(memtest ${SOURCE_PARSESO})

set(SOURCE_PARSESO  demo/DesignPatterns/Memento2.cpp)
add_executable(DesignPatterns ${SOURCE_PARSESO})

set(SOURCE_PARSESO  dl/dnn.cpp)
add_executable(dltest ${SOURCE_PARSESO})

#unique_resource
set(unique_resource_file unique_resource/test1.cpp)
add_executable(unique_resourcetest ${unique_resource_file})

#thread test
set(thread_test_file thread/main.cpp)
add_executable(thread_test ${thread_test_file})


#template test
set(template_test_file template/test/template_9.cpp)
add_executable(template_test ${template_test_file})

#target_link_libraries()