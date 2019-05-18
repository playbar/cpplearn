# demo

set(SOURCE_BASE CppBase/pthread_test.cpp)
add_executable(pthread_test ${SOURCE_BASE})
target_include_directories(pthread_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )


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

set(memleak_src
        memleak/main.cpp
        memleak/MemLeak.cpp
        )
add_executable(memleak ${memleak_src})

set(MEMORYDETECTOR_SRC
        memtest/MemoryDetector.cpp)
add_executable(MemoryDetector ${MEMORYDETECTOR_SRC})

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

##

set(SOURCE_UTILS
        utils/utils.cpp
        utils/md5.cpp
        utils/maintest.cpp)

add_executable(UtilsTest ${SOURCE_UTILS})
target_include_directories(UtilsTest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
        )

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


add_executable(meminfolinux
        meminfolinux.cpp)

add_executable(meminfomac
        meminfomac.cpp)

