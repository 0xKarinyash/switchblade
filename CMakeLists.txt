cmake_minimum_required(VERSION 3.21)
project(Switchblade C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_C_FLAGS_DEBUG "/Od /D_DEBUG /Zi")
    set(CMAKE_C_FLAGS_RELEASE "/O2 /D_NDEBUG")
endif()

add_executable(Switchblade WIN32
        src/main.c
        src/hook/hook.c
)

target_link_options(Switchblade PRIVATE "/ENTRY:mainCRTStartup")

target_include_directories(Switchblade PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hook
)