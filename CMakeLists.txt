cmake_minimum_required(VERSION 3.25)
project(gltest)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} 
    src/shader/fragmentShader.glsl
    src/shader/vertexShader.glsl
    src/fileio.c
    src/glad.c
    src/main.c
    src/shader.c
    src/texture.c
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${OPENGL_LIBRARIES}
        glfw
        m
)
