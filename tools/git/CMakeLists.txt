cmake_minimum_required(VERSION 3.4.1)

project(git LANGUAGES CXX C)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -O2 -g -W -Wall -Wno-unused-parameter -Wbad-function-cast -Wuninitialized")

add_definitions(-DNO_GETTEXT)
add_definitions(-DETC_GITATTRIBUTES="/etc/gitattributes")
#set(ETC_GITATTRIBUTES  /etc/gitattributes)

add_executable(git
        attr.c
        common-main.c)

target_include_directories(git PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )



#####
