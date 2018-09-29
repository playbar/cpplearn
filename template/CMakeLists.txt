#template test
set(template_test_file test/template_9.cpp)
add_executable(template_test ${template_test_file})

target_include_directories(template_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})