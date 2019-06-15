# demo

set(INHERIT_SRC inherit/test3.cpp)
add_executable(inherit_test
        ${INHERIT_SRC})
target_include_directories(inherit_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inherit
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
set(memleak_src
        memleak/main.cpp
        memleak/MemLeak.cpp
        )
add_executable(memleak ${memleak_src})

set(MEMORYDETECTOR_SRC
        memtest/MemoryDetector.cpp)
add_executable(MemoryDetector ${MEMORYDETECTOR_SRC})

##

add_executable(Utf8_test
        utf8/TestUtf8.cpp)
target_include_directories(Utf8_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/utf8
)

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

