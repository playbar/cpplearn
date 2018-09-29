#variant test
set(variant_test_file
        test/our_variant_hello_world.cpp)

add_executable(variant_test ${variant_test_file})
target_include_directories(variant_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include)


