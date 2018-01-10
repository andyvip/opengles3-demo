cmake_minimum_required(VERSION 3.4.1)

file(GLOB render_srcs "../../common/render/*.cpp")
file(GLOB jni_srcs "src/main/cpp/*.cpp")

include_directories(../../common/render)

add_library(render SHARED ${render_srcs} ${jni_srcs})

target_link_libraries(
    render
    android
    log
    EGL
    GLESv3
)