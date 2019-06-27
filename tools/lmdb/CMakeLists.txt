cmake_minimum_required(VERSION 3.4.1)

#set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -O2 -g -W -Wall -Wno-unused-parameter -Wbad-function-cast -Wuninitialized")

add_library(lmdb STATIC
        mdb.c
        midl.c
)

target_include_directories(lmdb PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

#####
