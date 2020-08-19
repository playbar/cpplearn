# src
add_subdirectory(llvm)

add_definitions(-D__STL_HAS_NAMESPACES)
add_definitions(-D__STL_USE_NEW_IOSTREAMS)
#add_definitions(-D__STL_CLASS_PARTIAL_SPECIALIZATION)
add_definitions(-D__STL_NO_EXCEPTION_HEADER)

add_executable(map_test map_test.cpp)
target_include_directories(map_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/llvm/include
        ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(smartptr_test
        smartptr_test.cpp
        smartptr_test.h
        myalloc.h)
target_include_directories(smartptr_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/llvm/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        )


add_executable(vector_test
        vector_test.cpp
        vector_test.h
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


add_executable(list_test
        stltest/list.cpp
        myalloc.h)
target_include_directories(list_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/stlsgi
        ${CMAKE_CURRENT_SOURCE_DIR}
        )
######
set(STLTEST_SRC stltest/random.cpp)
add_executable(stl_random ${STLTEST_SRC})
target_include_directories(stl_random PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        )


set(SOURCE_BASE stltest/regex.cpp)
add_executable(regex_test ${SOURCE_BASE})
target_include_directories(regex_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/llvm/include
        ${CMAKE_CURRENT_SOURCE_DIR}/stltest

        )


set(SOURCE_BASE stltest/static_cast.cpp)
add_executable(static_cast ${SOURCE_BASE})
target_include_directories(static_cast PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/llvm/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

set(STLTEST_DECLTYPE_SRC
        stltest/decltype.cpp)
add_executable(stltest_decltype ${STLTEST_DECLTYPE_SRC})
target_include_directories(stltest_decltype PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/llvm/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

file(GLOB std_move_src stltest/std_move5.cpp)
add_executable(std_move_test
        ${std_move_src})

add_executable(std_array
        stltest/array.cpp)
target_include_directories(std_array PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/llvm/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        )


add_executable(std_set stltest/set.cpp)
target_include_directories(std_set PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/llvm/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

add_executable(std_math stltest/cmath.cpp)
target_include_directories(std_math PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/llvm/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

