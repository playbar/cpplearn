#cnn
set(SOURCE_CNN
        cnn.cpp
        mat.cpp
        minst.cpp
        main.cpp)
add_executable(cnntest ${SOURCE_CNN})

target_include_directories(cnntest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})