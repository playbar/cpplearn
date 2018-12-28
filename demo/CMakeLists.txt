# demo
set(SOURCE_BASE CppBase/regex.cpp)
add_executable(regex ${SOURCE_BASE})
target_include_directories(regex PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )


set(SOURCE_BASE CppBase/static_cast.cpp)
add_executable(static_cast ${SOURCE_BASE})
target_include_directories(static_cast PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )


set(SOURCE_MEM memtest/memtest.cpp)
add_executable(memtest ${SOURCE_MEM})
target_include_directories(memtest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

set(SOURCE_DESIGNPATTERN  DesignPatterns/Memento2.cpp)
add_executable(DesignPatterns ${SOURCE_DESIGNPATTERN})
target_include_directories(DesignPatterns PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

#
set(SOURCE_GTEST
        gtest/sample1_unittest.cc
        gtest/sample1.cc)
add_executable(gtest_sample1 ${SOURCE_GTEST})
target_include_directories(gtest_sample1 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../gtest/googletest/include
        )
target_link_libraries(gtest_sample1 gtest_main)

#
set(SOURCE_TTEST
        gtest/funset.cpp
        gtest/test_TEST.cpp)
add_executable(gtest_test ${SOURCE_TTEST})
target_include_directories(gtest_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../gtest/googletest/include
        )
target_link_libraries(gtest_test gtest_main)