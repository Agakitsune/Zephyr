cmake_minimum_required(VERSION 3.22)
project(zephyr)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(USE_EXPERIMENTAL OFF CACHE BOOL "Usage of experimental C++ features (std::experimental) in Zephyr")

if (${USE_EXPERIMENTAL})
    message(
        WARNING
"Enabling Zephyr experimental features
Please note that this may cause compilation errors on Windows systems")
endif()

file(GLOB SOURCE
    ${PROJECT_SOURCE_DIR}/src/gl/*.cpp
    ${PROJECT_SOURCE_DIR}/src/glfw/*.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/*.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCE})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${imgui_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        GL
        GLEW
        glfw
)

if (LINUX AND NOT APPLE AND ${USE_EXPERIMENTAL})
    target_compile_options(${PROJECT_NAME}
        PUBLIC
            -DZEPHYR_EXPERIMENTAL
    )
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    if (LINUX AND NOT APPLE)
        target_compile_options(${PROJECT_NAME}
            PUBLIC
                -ggdb
                -g3
        )
    endif()

    add_executable(${PROJECT_NAME}_demo
        main.cpp
    )

    target_link_libraries(${PROJECT_NAME}_demo
        PUBLIC
            ${PROJECT_NAME}
    )
endif()
