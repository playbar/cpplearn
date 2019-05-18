# src
add_executable(map_test
        map_test.cpp
        )
target_include_directories(map_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/llvm/include
        ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(vector_test
        vector_test.cpp
        myalloc.h)
target_include_directories(vector_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/llvm/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        )



