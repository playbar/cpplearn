# linux core
set(MM_SOURCE_FILES
        mm/cma.c
         )

add_library(core_mm STATIC
        ${MM_SOURCE_FILES}
        )

target_include_directories(core_mm PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/ia64/include
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/arm64/include/uapi
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/uapi
        ${CMAKE_CURRENT_SOURCE_DIR}/mm
        )

#####

set(gen_init_cpio_FILES
        usr/gen_init_cpio.c
        )

add_executable(gen_init_cpio ${gen_init_cpio_FILES})
target_include_directories(gen_init_cpio PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gen_init_cpio
        core_mm)


