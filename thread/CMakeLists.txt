#thread test
set(thread_test_file
        main.cpp)
add_executable(thread_test ${thread_test_file})

file(GLOB MAIN3_SRC main3.cpp)
add_executable(thread_main3
        ${MAIN3_SRC})