# json
set(SOURCE_JSON  pretty.cpp)
add_executable(jsontest ${SOURCE_JSON})
target_include_directories(jsontest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )
