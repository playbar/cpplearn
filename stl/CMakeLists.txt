# src
add_definitions(-D__STL_HAS_NAMESPACES)
add_definitions(-D__STL_USE_NEW_IOSTREAMS)
add_definitions(-D__STL_CLASS_PARTIAL_SPECIALIZATION)

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

add_executable(vector_test1
        vector_test1.cpp
        myalloc.h)
target_include_directories(vector_test1 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/stlsgi
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

