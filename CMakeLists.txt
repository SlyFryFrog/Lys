cmake_minimum_required(VERSION 3.31)
project(Lys LANGUAGES CXX)

# Options
option(BUILD_DEMO "Build the demo project" ON)
option(LYS_CUSTOM_MAIN "Use a custom main entry point" ON)

# Compiler settings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -g")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Julia setup
set(JULIA_DIR /snap/julia/current)
include_directories(${JULIA_DIR}/include/julia)
link_directories(${JULIA_DIR}/lib)

# External libraries
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Source files
file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/macros.cpp
)

file(GLOB_RECURSE MODULES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm
)

# Target: library or executable
if (LYS_CUSTOM_MAIN)
    message(STATUS "Using custom main")
    add_library(${PROJECT_NAME} ${SOURCES})
else()
    message(STATUS "Using built-in main")
    add_executable(${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/entry.cpp
        ${SOURCES}
    )
endif()

# Add modules
if (MODULES)
    target_sources(${PROJECT_NAME} PUBLIC FILE_SET allModules TYPE CXX_MODULES FILES ${MODULES})
endif()

# Linking
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glm::glm
        glfw
        Vulkan::Vulkan
        OpenGL::GL
        GLEW::GLEW
        julia
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        "-Wl,-rpath,${JULIA_DIR}/lib"
)

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Subdirectories
if (BUILD_DEMO)
    add_subdirectory(demo)
endif()

# Compile commands for clangd
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/compile_commands.json
    )
endif()
