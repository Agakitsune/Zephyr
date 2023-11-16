cmake_minimum_required(VERSION 3.22)
project(zephyr)

include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(USE_EXPERIMENTAL OFF CACHE BOOL "Usage of experimental C++ features (std::experimental) in Zephyr")
set(USE_ANONYMOUS OFF CACHE BOOL "Usage of anonymous structs in Zephyr")
set(USE_DEBUG ON CACHE BOOL "Debug messages in Zephyr")

message("-- Zephyr experimental features: ${USE_EXPERIMENTAL}")
message("-- Zephyr anonymous structs: ${USE_ANONYMOUS}")
message("-- Zephyr debug messages: ${USE_DEBUG}")

if (USE_EXPERIMENTAL)
    message(WARNING "Enabling Zephyr experimental features
    Please note that this may cause compilation errors on Windows systems")
endif()

file(GLOB SOURCE
    ${PROJECT_SOURCE_DIR}/src/__head.cpp

    ${PROJECT_SOURCE_DIR}/src/gl/*.cpp
    ${PROJECT_SOURCE_DIR}/src/glfw/*.cpp
    ${PROJECT_SOURCE_DIR}/src/input/*.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/*.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCE})

find_package(OpenGL REQUIRED)

if (NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL not found")
endif()

set(GLEW_VERBOSE ON)
find_package(GLEW REQUIRED)

if (NOT GLEW_FOUND)
    message(FATAL_ERROR "GLEW not found")
endif()

find_library(GLFW_LIBRARIES glfw DOC "GLFW library" REQUIRED)

if (NOT GLFW_LIBRARIES)
    set(GLFW_FOUND FALSE)
else()
    set(GLFW_FOUND TRUE)
    message("-- GLFW found: ${GLFW_LIBRARIES}")
endif()

if (NOT GLFW_FOUND)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
    )

    FetchContent_GetProperties(glfw)
    if(NOT glfw_POPULATED)
        FetchContent_Populate(glfw)

        set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
        set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
        set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
        set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

        add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
    endif()

    set(GLFW_LIBRARIES glfw)
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${GLEW_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLFW_LIBRARIES}
)

if (LINUX AND NOT APPLE AND USE_EXPERIMENTAL)
    target_compile_options(${PROJECT_NAME}
        PUBLIC
            -DZEPHYR_EXPERIMENTAL
    )
endif()

if (LINUX AND NOT APPLE AND USE_ANONYMOUS)
    target_compile_options(${PROJECT_NAME}
        PUBLIC
            -DZEPHYR_USE_ANONYMOUS
    )
endif()

if (NOT ${CMAKE_BUILD_TYPE} OR ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    if (LINUX AND NOT APPLE)
        if (USE_DEBUG)
            target_compile_options(${PROJECT_NAME}
                PUBLIC
                    -DZEPHYR_DEBUG
            )
        endif()

        target_compile_options(${PROJECT_NAME}
            PUBLIC
                -ggdb
                -g3
                -Wall
                -Wextra
                -Wpedantic
                -Werror
        )
    endif()

    add_executable(${PROJECT_NAME}_demo
        main.cpp
    )

    target_link_libraries(${PROJECT_NAME}_demo
        PUBLIC
            ${PROJECT_NAME}
    )
else()
    if (LINUX AND NOT APPLE)
        target_compile_options(${PROJECT_NAME}
            PUBLIC
                -Wall
                -Wextra
                -Wpedantic
                -Werror
                -Wno-unused-parameter
                -Wno-unused-variable
                -Wno-unused-but-set-variable
                -Wno-unused-function
                -Wno-unused-result
                -Wno-unused-value
                -Wno-unused-label
                -Wno-unused-local-typedefs
                -Wno-unused-macros
                -Wno-unused-const-variable
        )
    endif()
endif()
