# src

add_library(vld vld.cpp)
target_include_directories(vld PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES
        VLDtest.cpp
        )
add_executable(VLDTest ${SOURCE_FILES})
target_include_directories(VLDTest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(VLDTest
        vld)


