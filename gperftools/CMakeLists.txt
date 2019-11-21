# gperftools

add_definitions(-DNDEBUG)

file(GLOB TCMALLOC_BASE_SRC
        src/base/*.cc
        src/base/*.c)

file(GLOB TCMALLOC_SRC
        src/*.cc)

set(TCMALLOC_SRCS
        src/central_freelist.cc
        src/common.cc
        src/emergency_malloc.cc
        src/emergency_malloc_for_stacktrace.cc
        src/fake_stacktrace_scope.cc
        src/heap-checker.cc
        src/heap-checker-bcad.cc
        src/heap-profile-table.cc
        src/heap-profiler.cc
        src/internal_logging.cc
        src/malloc_extension.cc
        src/malloc_hook.cc
        src/maybe_threads.cc
        src/memfs_malloc.cc
        src/memory_region_map.cc
        src/page_heap.cc
        src/profile-handler.cc
        src/profiledata.cc
        src/profiler.cc
        src/raw_printer.cc
        src/sampler.cc
        src/span.cc
        src/stack_trace_table.cc
        src/stacktrace.cc
        src/static_vars.cc
        src/symbolize.cc
        src/system-alloc.cc
        src/tcmalloc.cc
        src/thread_cache.cc
        )

add_library(tcmalloc STATIC
        ${TCMALLOC_BASE_SRC}
        ${TCMALLOC_SRCS})
target_include_directories(tcmalloc PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)


#######

add_executable(addressmap_unittest
        src/tests/addressmap_unittest.cc
        ${TCMALLOC_BASE_SRC}
        ${TCMALLOC_SRCS}
)

target_include_directories(addressmap_unittest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

target_link_libraries(addressmap_unittest
        tcmalloc
        )

#######

add_executable(tcmalloc_unittest
        src/tests/tcmalloc_unittest.cc
        src/tests/testutil.cc
        )

target_include_directories(tcmalloc_unittest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

target_link_libraries(tcmalloc_unittest
        tcmalloc
        )

#######


add_executable(tcmalloc_large_unittest
        src/tests/tcmalloc_large_unittest.cc
        src/tests/testutil.cc
        ${TCMALLOC_BASE_SRC}
        ${TCMALLOC_SRCS}
        )

target_include_directories(tcmalloc_large_unittest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

#target_link_libraries(tcmalloc_large_unittest
#        tcmalloc
#        )


########

add_executable(realloc_unittest
        src/tests/realloc_unittest.cc
        src/tests/testutil.cc
        ${TCMALLOC_BASE_SRC}
        ${TCMALLOC_SRCS}
        )

target_include_directories(realloc_unittest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

