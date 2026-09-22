cmake_minimum_required(VERSION 3.20)

project(RocketMC
    VERSION 0.1
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/game.cpp
    src/core/window.cpp
    src/core/input.cpp
    src/renderer/renderer.cpp
    src/game.cpp
    vendor/glad/src/glad.c
)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION
        ${PROJECT_SOURCE_DIR}/vendor/GLFW/lib/libglfw3.a
    INTERFACE_INCLUDE_DIRECTORIES
        ${PROJECT_SOURCE_DIR}/vendor/GLFW/include
) 

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/vendor/glad/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw
    opengl32
    gdi32
)


