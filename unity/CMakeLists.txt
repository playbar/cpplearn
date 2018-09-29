# UnityConfig
set(UnityFile
        UnityConfigFile.cpp
        UnityConfigFile.h
        UnityConfig.cpp)
add_executable(UnityConfig ${UnityFile})
target_include_directories(UnityConfig PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})
