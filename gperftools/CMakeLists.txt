# gperftools


file(GLOB TCMALLOC_BASE_SRC
        src/base/*.cc)

file(GLOB TCMALLOC_SRC
        src/*.cc)

add_library(tcmalloc STATIC
        ${TCMALLOC_BASE_SRC}
        ${TCMALLOC_SRC})
target_include_directories(tcmalloc PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)


#######

add_executable(addressmap_unittest
        src/tests/addressmap_unittest.cc
)

target_include_directories(addressmap_unittest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

target_link_libraries(addressmap_unittest
        tcmalloc)


