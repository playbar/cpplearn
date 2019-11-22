
set(install_suffix _1.0)


set(C_SRCS
        src/arena.c
        src/background_thread.c
        src/base.c
        src/bin_info.c
        src/bin.c
        src/bitmap.c
        src/ckh.c
        src/ctl.c
        src/div.c
        src/eset.c
        src/extent_dss.c
        src/extent_mmap.c
        src/extent.c
        src/hash.c
        src/hook.c
        src/jemalloc.c
        src/large.c
        src/log.c
        src/malloc_io.c
        src/mutex_pool.c
        src/mutex.c
        src/nstime.c
        src/pages.c
        src/prng.c
        src/prof_data.c
        src/prof_log.c
        src/prof.c
        src/rtree.c
        src/safety_check.c
        src/sc.c
        src/stats.c
        src/sz.c
        src/tcache.c
        src/test_hooks.c
        src/thread_event.c
        src/ticker.c
        src/tsd.c
        src/witness.c
        )

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  list(APPEND C_SRCS src/zone.c)
endif()

if(enable_valgrind)
  list(APPEND C_SRCS src/valgrind.c)
endif()


set(LIBJEMALLOCLIB jemalloc${install_suffix})
add_library(${LIBJEMALLOCLIB} STATIC ${C_SRCS})
target_include_directories(${LIBJEMALLOCLIB} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
# Now add shared library. Needed for integration tests
# and a benchmark

set(LIBJEMALLOCSO jemallocso${install_suffix})
add_library(${LIBJEMALLOCSO} SHARED ${C_SRCS})
target_include_directories(${LIBJEMALLOCSO} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

####

set(C_TESTLIB_SRCS
        test/src/btalloc.c
        test/src/btalloc_0.c
        test/src/btalloc_1.c
        test/src/math.c
        test/src/mq.c
        test/src/mtx.c
        test/src/SFMT.c
        test/src/test.c
        test/src/thd.c
        test/src/timer.c
        )

set(C_TESTLIB_UNIT jemalloc_unit_test)
add_library(${C_TESTLIB_UNIT}  STATIC ${C_TESTLIB_SRCS})
target_include_directories(${C_TESTLIB_UNIT} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/test/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(C_TESTLIB_STRESS jemalloc_test_stress)
add_library(${C_TESTLIB_STRESS} STATIC ${C_TESTLIB_SRCS})
target_include_directories(${C_TESTLIB_STRESS} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/test/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Microbench
set(TESTS_STRESS
        test/stress/microbench.c
        )

# Build benchmark
# This consumes C_JETLIB, Link to SO
foreach(sourcefile ${TESTS_STRESS})
  get_filename_component(exename ${sourcefile} NAME_WE)
  set(exename "${exename}")
  add_executable(${exename} ${sourcefile})

  target_include_directories(${exename} PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR}/test/include
          ${CMAKE_CURRENT_SOURCE_DIR}/include)

  target_compile_definitions(${exename} PRIVATE
          JEMALLOC_STRESS_TEST)

  target_link_libraries(${exename} ${C_JETLIB} ${C_TESTLIB_STRESS}
          ${LIBJEMALLOCLIB})
endforeach(sourcefile ${TESTS_UNIT})

######

set(TESTS_UNIT
        test/unit/a0.c
        test/unit/arena_reset.c
        test/unit/atomic.c
        test/unit/bitmap.c
        test/unit/ckh.c
        test/unit/decay.c
        test/unit/fork.c
        test/unit/hash.c
        test/unit/junk.c
        test/unit/junk_alloc.c
        test/unit/junk_free.c
        test/unit/mallctl.c
        test/unit/math.c
        test/unit/mq.c
        test/unit/mtx.c
        test/unit/ph.c
        test/unit/prng.c
        test/unit/prof_accum.c
        test/unit/prof_active.c
        test/unit/prof_gdump.c
        test/unit/prof_idump.c
        test/unit/prof_reset.c
        test/unit/prof_thread_name.c
        test/unit/ql.c
        test/unit/qr.c
        test/unit/rb.c
        test/unit/rtree.c
        test/unit/SFMT.c
        test/unit/size_classes.c
        test/unit/smoothstep.c
        test/unit/stats.c
        test/unit/ticker.c
        test/unit/nstime.c
        test/unit/tsd.c
        test/unit/witness.c
        test/unit/zero.c
        )


foreach(sourcefile ${TESTS_UNIT})
  get_filename_component(exename ${sourcefile} NAME_WE)
  set(exename "${exename}${install_suffix}")
  add_executable(${exename} ${sourcefile})

  target_include_directories(${exename} PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR}/test/include
          ${CMAKE_CURRENT_SOURCE_DIR}/include)

  if(C_UNIT_TEST_CFLAGS)
    target_compile_options(${exename} PRIVATE
            "${C_UNIT_TEST_CFLAGS}")
  endif()

  set_target_properties(${exename}
          PROPERTIES
          COMPILE_DEFINITIONS
          "${C_UNITETEST_DEFS}"
          )

  target_link_libraries(${exename} ${C_JETLIB} ${C_TESTLIB_UNIT})

endforeach(sourcefile ${TESTS_UNIT})


####

set(TESTS_INTEGRATION
        test/integration/aligned_alloc.c
        test/integration/allocated.c
        test/integration/sdallocx.c
        test/integration/mallocx.c
        test/integration/MALLOCX_ARENA.c
        test/integration/overflow.c
        test/integration/posix_memalign.c
        test/integration/rallocx.c
        test/integration/thread_arena.c
        test/integration/thread_tcache_enabled.c
        test/integration/xallocx.c
        )

#######################################################################
# Build integration tests
# This links to SO library and UTIL_INTEGRATION
foreach(sourcefile ${TESTS_INTEGRATION})
  get_filename_component(exename ${sourcefile} NAME_WE)
  set(exename "${exename}${install_suffix}")
  add_executable(${exename} ${sourcefile} )

  target_include_directories(${exename} PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR}/test/include
          ${CMAKE_CURRENT_SOURCE_DIR}/include)

  target_compile_definitions(${exename} PRIVATE
          JEMALLOC_INTEGRATION_TEST)

  target_link_libraries(${exename} ${C_TESTLIB_INTEGRATION} ${LIBJEMALLOCLIB})

endforeach(sourcefile ${TESTS_UNIT})





