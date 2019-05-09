# src

add_subdirectory(stlsgi)
add_subdirectory(stltiny)

set(SOURCE_FILES
        vector_test.cpp
        )

add_executable(vector_test ${SOURCE_FILES})
target_include_directories(vector_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        )


