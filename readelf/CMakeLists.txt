# elf
set(SOURCE_READELF
        arm.h
        bfd.h
        dwarf2.cpp
        dwarf2.h
        elf.h
        hash.cpp
        objalloc.cpp
        objalloc.h
        ReadELF.cpp
        section.cpp
        )

add_executable(readelf ${SOURCE_READELF})

target_include_directories(readelf PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

########

set(SOURCE_PARSESO
        ParseSo.cpp
        elf2.h)
add_executable(ParseSo ${SOURCE_PARSESO})
target_include_directories(ParseSo PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})