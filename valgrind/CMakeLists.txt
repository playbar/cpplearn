# valgrind

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -std=c++14 -Ipriv  -m64 -O2 -g -Wall -Wmissing-prototypes -Wshadow -Wpointer-arith -Wstrict-prototypes -Wmissing-declarations -Wcast-align -Wcast-qual -Wwrite-strings -Wempty-body -Wformat -Wformat-security -Wignored-qualifiers -Wmissing-parameter-type -Wlogical-op -Wold-style-declaration -finline-functions -fno-stack-protector -fno-strict-aliasing -fno-builtin  -fomit-frame-pointer  -Wbad-function-cast -fstrict-aliasing")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -fvisibility=hidden -Ipriv  -m64 -O2 -g -Wall -Wmissing-prototypes -Wshadow -Wpointer-arith -Wstrict-prototypes -Wmissing-declarations -Wcast-align -Wcast-qual -Wwrite-strings -Wempty-body -Wformat -Wformat-security -Wignored-qualifiers -Wmissing-parameter-type -Wlogical-op -Wold-style-declaration -finline-functions -fno-stack-protector -fno-strict-aliasing -fno-builtin  -fomit-frame-pointer  -Wbad-function-cast -fstrict-aliasing")


add_definitions(-DNDEBUG)
add_definitions(-DVGA_amd64=1)
add_definitions(-DVGO_linux=1)
add_definitions(-DVGP_amd64_linux=1)
add_definitions(-DVGPV_amd64_linux_vanilla=1)

file(GLOB COREGRIND_DEBUGINFO_SRC
        coregrind/m_debuginfo/*.c)

#file(GLOB TCMALLOC_SRC
#        src/*.cc)
#
#
#
#set(HEAP_CHECKER_SRCS
#        src/heap-checker.cc
#        src/heap-checker-bcad.cc
#        )
#
#set(HEAP_PROFILE_SRCS
#        src/heap-profile-table.cc
#        src/heap-profiler.cc
#        )
#
#set(CPU_PROFILE_SRCS
#
#        )
#
set(COREGRIND_SRCS
        coregrind/m_addrinfo.c
        coregrind/m_aspacehl.c
        coregrind/m_cache.c
        coregrind/m_clientstate.c
        coregrind/m_commandline.c
        coregrind/m_compiler.c
        coregrind/m_debuglog.c
        coregrind/m_deduppoolalloc.c
        coregrind/m_errormgr.c
        coregrind/m_execontext.c
        coregrind/m_hashtable.c
        coregrind/m_libcassert.c
        coregrind/m_libcfile.c
        coregrind/m_libcprint.c
        coregrind/m_libcproc.c
        coregrind/m_libcsetjmp.c
        coregrind/m_libcsignal.c
        coregrind/m_machine.c
#        coregrind/m_main.c
        coregrind/m_mallocfree.c
        coregrind/m_options.c
        coregrind/m_oset.c
        coregrind/m_poolalloc.c
        coregrind/m_rangemap.c
        coregrind/m_redir.c
        coregrind/m_sbprofile.c
        coregrind/m_seqmatch.c
        coregrind/m_signals.c
        coregrind/m_sparsewa.c
        coregrind/m_stacks.c
        coregrind/m_stacktrace.c
        coregrind/m_syscall.c
        coregrind/m_threadstate.c
        coregrind/m_tooliface.c
        coregrind/m_trampoline.S
        coregrind/m_translate.c
        coregrind/m_transtab.c
        coregrind/m_vki.c
        coregrind/m_vkiscnums.c
        coregrind/m_wordfm.c
        coregrind/m_xarray.c
        coregrind/m_xtmemory.c
        coregrind/m_xtree.c
        )

#add_library(coregrind STATIC
#        ${COREGRIND_DEBUGINFO_SRC}
#        ${COREGRIND_SRCS}
#        )
#target_include_directories(coregrind PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}
#        ${CMAKE_CURRENT_SOURCE_DIR}/VEX/pub
#        ${CMAKE_CURRENT_SOURCE_DIR}/include
#        ${CMAKE_CURRENT_SOURCE_DIR}/coregrind
#)


#######

#add_executable(memcheck
#        memcheck/mc_errors.c
#        memcheck/mc_leakcheck.c
#        memcheck/mc_machine.c
#        memcheck/mc_main.c
#        memcheck/mc_malloc_wrappers.c
#        memcheck/mc_translate.c
#)
#
#target_include_directories(memcheck PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}
#        ${CMAKE_CURRENT_SOURCE_DIR}/include
#        ${CMAKE_CURRENT_SOURCE_DIR}/memcheck
#        ${CMAKE_CURRENT_SOURCE_DIR}/VEX/pub
#        )
#
#target_link_libraries(memcheck
#        coregrind
#        )

#######

add_executable(valgrind_test
        valgrind_test.cpp
        )

target_include_directories(valgrind_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/
        )



