#thread test
file(GLOB professional_cpp_src
        c01_code/05_StronglyTypedEnums/*.cpp
        )
add_executable(professional_cpp ${professional_cpp_src})
target_include_directories(professional_cpp PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})
