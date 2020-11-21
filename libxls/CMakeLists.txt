add_definitions(-DHAVE_ICONV)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/inlcude
)

add_library(libxls STATIC
        src/endian.c
        src/locale.c
        src/ole.c
        src/xls.c
        src/xlstool.c)


add_executable(xlscpp cplusplus/main.cpp cplusplus/XlsReader.cpp)
target_link_libraries(xlscpp libxls)

add_executable(xls2csv src/xls2csv.c)
target_link_libraries(xls2csv libxls)

add_executable(test test/test.c)
target_link_libraries(test libxls iconv)

add_executable(test2 test/test2.c)
target_link_libraries(test2 libxls)


