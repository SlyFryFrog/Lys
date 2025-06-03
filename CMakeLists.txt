cmake_minimum_required(VERSION 3.31)
project(Lys LANGUAGES CXX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Compiler settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (LINUX)
    # Append -fPIC to CMAKE_CXX_FLAGS for shared library compilation
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

# Options
option(BUILD_DEMO "Build the demo project" ON)
option(LYS_CUSTOM_MAIN "Use a custom main entry point" ON)

# --- START: Julia and JlCxx setup ---

# if(NOT CXXWRAP_PREFIX_PATH)
#     message(FATAL_ERROR "CXXWRAP_PREFIX_PATH is not set. Please provide it using -DCXXWRAP_PREFIX_PATH=<path_from_CxxWrap.prefix_path()>")
# endif()

# # Prepend our specific CXXWRAP_PREFIX_PATH to CMAKE_PREFIX_PATH
# # This makes find_package aware of where to look for JlCxx
# list(APPEND CMAKE_PREFIX_PATH "${CXXWRAP_PREFIX_PATH}")

# # Find JlCxx (which is part of CxxWrap.jl's C++ components)
# find_package(JlCxx REQUIRED)

# if (LINUX)
#     set(JULIA_DIR /home/marcus/.julia/juliaup/julia-1.11.5+0.x64.linux.gnu)
# else()
#     set(JULIA_DIR /opt/homebrew/Cellar/julia/1.11.5)
# endif()
# include_directories(${JULIA_DIR}/include/julia) # Include Julia's headers
# link_directories(${JULIA_DIR}/lib) # Link Julia's libraries

# --- END: Julia and JlCxx setup ---

# External libraries
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# <-- Vulkan setup -->
find_package(Vulkan REQUIRED)
find_package(VulkanHeaders CONFIG REQUIRED)

# Require Vulkan version ≥ 1.3.256 (earliest version when the Vulkan module was available)
if( ${Vulkan_VERSION} VERSION_LESS "1.3.256" )
  message( FATAL_ERROR "Minimum required Vulkan version for C++ modules is 1.3.256. "
           "Found ${Vulkan_VERSION}."
  )
endif()

# set up Vulkan C++ module as a library
add_library(VulkanHppModule)
target_sources(VulkanHppModule 
    PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS ${Vulkan_INCLUDE_DIR}
        FILES ${Vulkan_INCLUDE_DIR}/vulkan/vulkan.cppm
)
target_compile_features(VulkanHppModule PUBLIC cxx_std_23)
target_link_libraries(VulkanHppModule PRIVATE Vulkan::Vulkan Vulkan::Headers)
# <-- End of vulkan setup -->

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
    target_sources(
        ${PROJECT_NAME} 
        PUBLIC 
            FILE_SET allModules 
            TYPE CXX_MODULES 
            FILES ${MODULES}
    )
endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_link_libraries(
    ${PROJECT_NAME}
    # PRIVATE
    PUBLIC
        glm::glm
        glfw
        VulkanHppModule
        OpenGL::GL
        GLEW::GLEW
    # PUBLIC
    #     julia
    #     JlCxx::cxxwrap_julia
)

# Include directories
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
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