# src
set(SOURCE_FILES
        main.cpp
        CTest.cpp )
add_executable(CLionTest ${SOURCE_FILES})
target_include_directories(CLionTest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

###
set(SOURCE_NTH
        nth_element.cpp)
add_executable(nth_element ${SOURCE_NTH})
target_include_directories(nth_element PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})
