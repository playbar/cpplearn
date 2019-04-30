cmake_minimum_required(VERSION 3.4.1)

#boost_1_70_0

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -fexceptions -frtti -fPIC")

add_library(boost_test STATIC
        libs/test/src/compiler_log_formatter.cpp
        libs/test/src/cpp_main.cpp
        libs/test/src/debug.cpp
        libs/test/src/decorator.cpp
        libs/test/src/execution_monitor.cpp
        libs/test/src/framework.cpp
        libs/test/src/junit_log_formatter.cpp
        libs/test/src/plain_report_formatter.cpp
        libs/test/src/progress_monitor.cpp
        libs/test/src/results_collector.cpp
        libs/test/src/results_reporter.cpp
        libs/test/src/test_framework_init_observer.cpp
        libs/test/src/test_tools.cpp
        libs/test/src/test_tree.cpp
        libs/test/src/unit_test_log.cpp
        libs/test/src/unit_test_monitor.cpp
        libs/test/src/unit_test_parameters.cpp
        libs/test/src/xml_log_formatter.cpp
        libs/test/src/xml_report_formatter.cpp
        )

target_include_directories(boost_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/test
        )

#####

add_library(boost_all STATIC
        libs/thread/src/pthread/thread.cpp
        libs/thread/src/pthread/once.cpp
        libs/filesystem/src/codecvt_error_category.cpp
        libs/filesystem/src/operations.cpp
        libs/filesystem/src/path.cpp
        libs/filesystem/src/path_traits.cpp
        libs/filesystem/src/portability.cpp
        libs/filesystem/src/unique_path.cpp
        libs/filesystem/src/utf8_codecvt_facet.cpp
        libs/system/src/error_code.cpp
        libs/program_options/src/cmdline.cpp
        libs/program_options/src/config_file.cpp
        libs/program_options/src/convert.cpp
        libs/program_options/src/options_description.cpp
        libs/program_options/src/parsers.cpp
        libs/program_options/src/positional_options.cpp
        libs/program_options/src/split.cpp
        libs/program_options/src/utf8_codecvt_facet.cpp
        libs/program_options/src/value_semantic.cpp
        libs/program_options/src/variables_map.cpp
        )


target_include_directories(boost_all PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/filesystem/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/math/include_private
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/thread/include
        )


###
add_executable(accumulators_count
        libs/accumulators/test/count.cpp
        )
target_include_directories(accumulators_count PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/filesystem/include
        )
target_link_libraries(accumulators_count
        boost_test
        boost_all)

######
add_executable(algorithm_all_test
        libs/algorithm/test/all_of_test.cpp
        )
target_include_directories(algorithm_all_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/filesystem/include
        )
target_link_libraries(algorithm_all_test
        boost_test
        boost_all)



######
add_executable(filesystem_convenience_test
        libs/filesystem/test/convenience_test.cpp
        )
target_include_directories(filesystem_convenience_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/filesystem/include
        )
target_link_libraries(filesystem_convenience_test
        boost_test
        boost_all)

#######

######
add_executable(boost_test1
        tests/test1.cpp
        )
target_include_directories(boost_test1 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )
target_link_libraries(boost_test1
        boost_test
        boost_all)

#######

