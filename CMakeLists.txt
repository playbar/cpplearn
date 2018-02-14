cmake_minimum_required(VERSION 3.6)
project(cpplearn)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fpermissive -fvisibility=hidden -Wall -std=c++11" )

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/CTest.cpp src/CTest.h parseso/ParseSo.cpp src/nth_element.cpp src/threadtest.cpp)
add_executable(CLionTest ${SOURCE_FILES})

MESSAGE("make files")


set(SOURCE_FILES1 src/main2.cpp src/CTest.cpp )
add_executable(CLionTest2 ${SOURCE_FILES1})

set(SOURCE_PARSESO parseso/ParseSo.cpp parseso/elf.h)
add_executable(ParseSo ${SOURCE_PARSESO})


set(SOURCE_READELF readelf/arm.h readelf/bfd.h
                    readelf/dwarf2.cpp readelf/dwarf2.h
                    readelf/elf.h readelf/hash.cpp
                    readelf/objalloc.cpp readelf/objalloc.h
                    readelf/ReadELF.cpp readelf/section.cpp)
add_executable(readelf ${SOURCE_READELF})


set(SOURCE_PARSESO src/usingtest.cpp src/nth_element.cpp)
add_executable(UsingTest ${SOURCE_PARSESO})


set(SOURCE_PARSESO demo/CppBase/functional.cpp)
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

#target_link_libraries()