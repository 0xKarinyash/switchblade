cmake_minimum_required(VERSION 3.21)
project(Switchblade C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(Switchblade WIN32
        src/main.c
        src/hook/hook.c
)

add_executable(Switchblade-static WIN32
        src/main.c
        src/hook/hook.c
)
set_target_properties(Switchblade-static PROPERTIES
    OUTPUT_NAME "Switchblade-static"
)

if(MSVC)
    target_compile_options(Switchblade PRIVATE
            $<$<CONFIG:Debug>:/Od /Zi>
            $<$<CONFIG:Release>:/O2>
    )
    target_link_options(Switchblade PRIVATE "/ENTRY:mainCRTStartup")

    set_property(TARGET Switchblade-static PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    target_compile_options(Switchblade-static PRIVATE
            $<$<CONFIG:Debug>:/Od /Zi>
            $<$<CONFIG:Release>:/O2>
    )
    target_link_options(Switchblade-static PRIVATE "/ENTRY:mainCRTStartup")
else()
    target_compile_options(Switchblade PRIVATE
            $<$<CONFIG:Debug>:-g>
            $<$<CONFIG:Release>:-O2>
    )

    target_compile_options(Switchblade-static PRIVATE
            $<$<CONFIG:Debug>:-g>
            $<$<CONFIG:Release>:-O2>
    )
    target_link_options(Switchblade-static PRIVATE -static)
endif()

target_include_directories(Switchblade PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hook
)

target_include_directories(Switchblade-static PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hook
)