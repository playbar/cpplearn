cmake_minimum_required(VERSION 3.6)
project(cpplearn)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fpermissive -fvisibility=hidden -Wall -std=c++14" )

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/CTest.cpp )
add_executable(CLionTest ${SOURCE_FILES})

MESSAGE("make files")

message(${CMAKE_CXX_COMPILER_ID})


set(SOURCE_FILES1 thread/main2.cpp src/CTest.cpp )
add_executable(CLionTest2 ${SOURCE_FILES1})

set(SOURCE_PARSESO parseso/ParseSo.cpp parseso/elf.h)
add_executable(ParseSo ${SOURCE_PARSESO})


set(SOURCE_READELF readelf/arm.h readelf/bfd.h
                    readelf/dwarf2.cpp readelf/dwarf2.h
                    readelf/elf.h readelf/hash.cpp
                    readelf/objalloc.cpp readelf/objalloc.h
                    readelf/ReadELF.cpp readelf/section.cpp)
add_executable(readelf ${SOURCE_READELF})


set(SOURCE_PARSESO src/nth_element.cpp)
add_executable(nth_element ${SOURCE_PARSESO})


set(SOURCE_PARSESO demo/CppBase/optional.cpp)
add_executable(CppBase ${SOURCE_PARSESO})


set(SOURCE_PARSESO  demo/DesignPatterns/Memento2.cpp)
add_executable(DesignPatterns ${SOURCE_PARSESO})


set(SOURCE_PARSESO  sqlitetest/sqlite3.c sqlitetest/stmttest.cpp)
add_executable(sqlitetest ${SOURCE_PARSESO})

set(SOURCE_PARSESO  sqlitetest/sqlite3.c sqlitetest/shell.c)
add_executable(sqlite3 ${SOURCE_PARSESO})


set(SOURCE_PARSESO  dl/dnn.cpp)
add_executable(dltest ${SOURCE_PARSESO})

set(SOURCE_PARSESO  cnn/cnn.cpp cnn/mat.cpp cnn/minst.cpp cnn/main.cpp)
add_executable(cnntest ${SOURCE_PARSESO})

# UnityConfig
set(UnityFile  unity/UnityConfigFile.cpp unity/UnityConfigFile.h unity/UnityConfig.cpp)
add_executable(UnityConfig ${UnityFile})


# json
set(SOURCE_PARSESO  json/pretty.cpp)
add_executable(jsontest ${SOURCE_PARSESO})
target_include_directories(jsontest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/json
        )

#unique_resource
set(unique_resource_file unique_resource/test1.cpp)
add_executable(unique_resourcetest ${unique_resource_file})

#thread test
set(thread_test_file thread/main.cpp)
add_executable(thread_test ${thread_test_file})


#template test
set(template_test_file template/test/7.cpp)
add_executable(template_test ${template_test_file})


#variant test
set(variant_test_file variant/test/our_variant_hello_world.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/variant/include)
add_executable(variant_test ${variant_test_file})

#crypto-aes
set(crypto_aes_src crypto/aes/main.c crypto/aes/aes.c)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/crypto/aes)
add_executable(crypto_aes ${crypto_aes_src})

#crypto-aes_1
set(crypto_aes_1_src crypto/aes_1/test.c crypto/aes_1/aes.c)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/crypto/aes_1)
add_executable(crypto_aes_1 ${crypto_aes_1_src})

#target_link_libraries()