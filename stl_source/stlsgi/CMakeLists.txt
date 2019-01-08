# src
set(SOURCE_FILES
        test/vector_test.cpp
        )

add_executable(sgi_vector_test ${SOURCE_FILES})
target_include_directories(sgi_vector_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

