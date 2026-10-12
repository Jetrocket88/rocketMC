cmake_minimum_required(VERSION 3.20)

project(RocketMC
    VERSION 0.1
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glm CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/game.cpp

    src/core/window.cpp
    src/core/input.cpp
    src/core/frame_timer.cpp

    src/renderer/renderer.cpp
    src/assets/asset_manager.cpp

    src/renderer/shader.cpp
    src/renderer/camera.cpp

    src/renderer/texture.cpp

    src/gameplay/chunk.cpp
    src/gameplay/world.cpp


    vendor/glad/src/glad.c
)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION
        ${PROJECT_SOURCE_DIR}/vendor/GLFW/lib/libglfw3.a
    INTERFACE_INCLUDE_DIRECTORIES
        ${PROJECT_SOURCE_DIR}/vendor/GLFW/include
) 

add_library(stb_image STATIC ${PROJECT_SOURCE_DIR}/vendor/stb/stb_image.cpp)
target_include_directories(stb_image SYSTEM PUBLIC ${PROJECT_SOURCE_DIR}/vendor/stb)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/vendor/glad/include
    ${PROJECT_SOURCE_DIR}/vendor/stb
)
target_link_libraries(${PROJECT_NAME} PRIVATE stb_image)

target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw
    opengl32
    gdi32
)


