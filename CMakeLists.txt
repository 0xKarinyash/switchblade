cmake_minimum_required(VERSION 3.21)
project(Switchblade C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(Switchblade WIN32
        src/main.c
        src/hook/hook.c
)

if(MSVC)
    target_compile_options(Switchblade PRIVATE
            $<$<CONFIG:Debug>:/Od /Zi>
            $<$<CONFIG:Release>:/O2>
    )
    target_link_options(Switchblade PRIVATE "/ENTRY:mainCRTStartup")
else()
    target_compile_options(Switchblade PRIVATE
            $<$<CONFIG:Debug>:-g>
            $<$<CONFIG:Release>:-O2>
    )
endif()

target_include_directories(Switchblade PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hook
)