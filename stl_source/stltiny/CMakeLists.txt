# src
set(SOURCE_FILES
        main.cpp
        )

add_executable(stltiny_test ${SOURCE_FILES})
target_include_directories(stltiny_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Test
        )
