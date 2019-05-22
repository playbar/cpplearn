# src

#add_definitions(-D__STL_USE_NEW_IOSTREAMS )
add_definitions(-D__STL_NO_EXCEPTION_HEADER)

set(SOURCE_FILES
        test/vector_test.cpp
        )

add_executable(sgi_stl_test ${SOURCE_FILES})
target_include_directories(sgi_stl_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

