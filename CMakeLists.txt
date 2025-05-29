cmake_minimum_required(VERSION 3.31)
project(Lys LANGUAGES CXX)

# Compiler settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# You removed CMAKE_CXX_FLAGS "-fPIC -g" from your original code.
# If you still need these flags, you should add them back here:
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -g")


# Options
option(BUILD_DEMO "Build the demo project" ON)
option(LYS_CUSTOM_MAIN "Use a custom main entry point" ON)

# --- START: Julia and JlCxx setup ---

if(NOT CXXWRAP_PREFIX_PATH)
    message(FATAL_ERROR "CXXWRAP_PREFIX_PATH is not set. Please provide it using -DCXXWRAP_PREFIX_PATH=<path_from_CxxWrap.prefix_path()>")
endif()

# Prepend our specific CXXWRAP_PREFIX_PATH to CMAKE_PREFIX_PATH
# This makes find_package aware of where to look for JlCxx
list(APPEND CMAKE_PREFIX_PATH "${CXXWRAP_PREFIX_PATH}")

# Find JlCxx (which is part of CxxWrap.jl's C++ components)
find_package(JlCxx REQUIRED)

if (LINUX)
    set(JULIA_DIR /snap/julia/current)
else()
    set(JULIA_DIR /opt/homebrew/Cellar/julia/1.11.5)
endif()
include_directories(${JULIA_DIR}/include/julia) # Include Julia's headers
link_directories(${JULIA_DIR}/lib) # Link Julia's libraries

# --- END: Julia and JlCxx setup ---

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
    add_library(${PROJECT_NAME} SHARED ${SOURCES})
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

# --- FIX: Add target_compile_features for C++ Modules support ---
# This explicitly tells CMake that the target uses C++20 features (like modules),
# even if CMAKE_CXX_STANDARD is already set.
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

# Linking
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        glm::glm
        glfw
        Vulkan::Vulkan
        OpenGL::GL
        GLEW::GLEW
    PUBLIC
        julia
        JlCxx::cxxwrap_julia
)

target_link_options(
    ${PROJECT_NAME}
    PUBLIC
        "-Wl,-rpath,${JULIA_DIR}/lib"
        # Adding CXXWRAP_PREFIX_PATH/lib to rpath might be necessary if JlCxx components
        # are not found at runtime. Keep it for now.
        "-Wl,-rpath,${CXXWRAP_PREFIX_PATH}/lib"
)

# Include directories
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        # Add JlCxx's include directory, provided by find_package(JlCxx)
        ${JlCxx_INCLUDE_DIRS}
)

# Subdirectories
if (BUILD_DEMO)
    # The 'demo' subdirectory will also need its own target_compile_features call
    # if it uses C++ Modules. You'll need to add it to demo/CMakeLists.txt as well.
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