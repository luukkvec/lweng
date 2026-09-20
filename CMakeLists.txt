cmake_minimum_required(VERSION 3.20)

project(lweng LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lweng
    src/main.cpp
    src/engine/engine.cpp
    src/engine/graphics/renderer.cpp
    src/engine/window.cpp
    src/engine/graphics/shader.cpp
    third_party/glad/src/gl.c
    src/engine/game/camera.cpp
)

target_include_directories(lweng PRIVATE
    src
    third_party/SDL2/include
    third_party/glad/include
    third_party/glm/glm
)

target_link_directories(lweng PRIVATE
    third_party/SDL2/lib/x64
)

target_link_libraries(lweng PRIVATE
    SDL2
)