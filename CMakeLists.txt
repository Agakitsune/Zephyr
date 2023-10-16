cmake_minimum_required(VERSION 3.22)
project(zephyr)

# include(FetchContent)

# function(downloadFile url name_)

#     FetchContent_Declare(${name_}
#         URL ${url}
#     )

#     FetchContent_Populate(${name_})

# endfunction(downloadFile)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# downloadFile("https://github.com/ocornut/imgui/archive/refs/heads/docking.zip" IMGUI)

# FetchContent_MakeAvailable(IMGUI)

file(GLOB SOURCE
    ${PROJECT_SOURCE_DIR}/src/gl/*.cpp
    ${PROJECT_SOURCE_DIR}/src/glfw/*.cpp
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

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    if (UNIX)
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
