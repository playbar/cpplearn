# src
set(SOURCE_FILES
        list.c
        tlsf.c
        tlsf_help.cpp
        test.cpp
         )
add_executable(tlsf_test ${SOURCE_FILES})
target_include_directories(tlsf_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})


