#thread test
set(regex_file
        regex.c
        regex_test.cpp)
add_executable(regex_test ${regex_file})
target_include_directories(regex_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})
