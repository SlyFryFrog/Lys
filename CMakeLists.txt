cmake_minimum_required(VERSION 3.28)
project(Lys LANGUAGES CXX)

# Compiler settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(BUILD_DEMO "Build the demo project" ON)
option(LYS_CUSTOM_MAIN "Use a custom main entry point" ON)
option(BUILD_SCRIPTING_SUPPORT "Enable Julia/JlCxx scripting support" ON)

# <-- Start: Julia and JlCxx setup -->
#if(BUILD_SCRIPTING_SUPPORT)
#     if(NOT CXXWRAP_PREFIX_PATH)
#         message(FATAL_ERROR "CXXWRAP_PREFIX_PATH is not set. Please provide it using -DCXXWRAP_PREFIX_PATH=<path_from_CxxWrap.prefix_path()>")
#     endif()
#
#     # Prepend our specific CXXWRAP_PREFIX_PATH to CMAKE_PREFIX_PATH
#     # This makes find_package aware of where to look for JlCxx
#     list(APPEND CMAKE_PREFIX_PATH "${CXXWRAP_PREFIX_PATH}")
#
#     # Find JlCxx (which is part of CxxWrap.jl's C++ components)
#     find_package(JlCxx REQUIRED)
#
#     include_directories(${JULIA_DIR}/include/julia) # Include Julia's headers
#     link_directories(${JULIA_DIR}/lib) # Link Julia's libraries
#endif()
# <-- End: Julia and JlCxx setup -->

# External libraries
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# <-- Start: Vulkan setup -->
find_package(Vulkan REQUIRED)
find_package(VulkanHeaders CONFIG REQUIRED)

# Require Vulkan version ≥ 1.3.256 (earliest version when the Vulkan module was available)
if( ${Vulkan_VERSION} VERSION_LESS "1.3.256" )
    message( FATAL_ERROR "Minimum required Vulkan version for C++ modules is 1.3.256. "
           "Found ${Vulkan_VERSION}."
    )
endif()

# Set up Vulkan C++ module as a library
add_library(VulkanHppModule)
target_sources(VulkanHppModule
    PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS ${Vulkan_INCLUDE_DIR}
        FILES ${Vulkan_INCLUDE_DIR}/vulkan/vulkan.cppm
)

target_link_libraries(VulkanHppModule PRIVATE Vulkan::Vulkan Vulkan::Headers)
# <-- End: vulkan setup -->

# Glob all headers, sources, and modules
file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/macros.cpp
)

file(GLOB_RECURSE MODULES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm)

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
    target_sources(
        ${PROJECT_NAME}
        PUBLIC
            FILE_SET allModules
            TYPE CXX_MODULES
            FILES ${MODULES}
    )
endif()


if (APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif()

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        glm::glm
        glfw
        VulkanHppModule
        OpenGL::GL
        GLEW::GLEW
#        julia
#        JlCxx::cxxwrap_julia
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