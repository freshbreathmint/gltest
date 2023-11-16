cmake_minimum_required(VERSION 3.25)

project(gltest)

find_package(OpenGL REQUIRED)

# Provide an option for the user to choose the compiler
option(USE_MINGW "Use Mingw-w64 compiler" OFF)

# Set default compilers
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# If Mingw-w64 option is enabled, use Mingw-w64 compilers
if(USE_MINGW)
    find_program(MINGW_GCC_COMPILER NAMES x86_64-w64-mingw32-gcc i686-w64-mingw32-gcc)
    find_program(MINGW_GPP_COMPILER NAMES x86_64-w64-mingw32-g++ i686-w64-mingw32-g++)
    
    if(MINGW_GCC_COMPILER AND MINGW_GPP_COMPILER)
        set(CMAKE_C_COMPILER "${MINGW_GCC_COMPILER}")
        set(CMAKE_CXX_COMPILER "${MINGW_GPP_COMPILER}")
    else()
        message(FATAL_ERROR "Mingw-w64 compilers not found. Please install Mingw-w64 or disable USE_MINGW option.")
    endif()
endif()

include_directories(${OPENGL_INCLUDE_DIRS})

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_subdirectory( glfw )

add_executable(${PROJECT_NAME} 
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

# Output
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# Define the source and destination.
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)
set(RESOURCES_DEST ${CMAKE_SOURCE_DIR}/bin/resources)

# Copy resources
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCES_DIR} ${RESOURCES_DEST}
)

# Define a custom target to trigger the resource copy
add_custom_target(copy_resources ALL
    DEPENDS ${RESOURCES_DEST}
)