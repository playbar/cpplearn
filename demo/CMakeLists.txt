# demo
set(SOURCE_BASE CppBase/map.cpp)
add_executable(CppBase ${SOURCE_BASE})
target_include_directories(CppBase PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )



set(SOURCE_MEM memtest/MemoryDetector.cpp)
add_executable(memtest ${SOURCE_MEM})
target_include_directories(memtest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

set(SOURCE_DESIGNPATTERN  DesignPatterns/Memento2.cpp)
add_executable(DesignPatterns ${SOURCE_DESIGNPATTERN})
target_include_directories(DesignPatterns PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )
