cmake_minimum_required(VERSION 3.31)
project(Lys LANGUAGES CXX)

set(BUILD_DEMO 1)
set(LYS_CUSTOM_MAIN 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/macros.cpp)
file(GLOB_RECURSE MODULES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm)

# Decide whether to build as library or executable
if (LYS_CUSTOM_MAIN)
    message("Using custom main")
    add_library(${PROJECT_NAME} ${SOURCES})
else()
    message("Using built-in main")
    add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main/entry.cpp ${SOURCES})
endif()

target_sources(${PROJECT_NAME} PUBLIC FILE_SET allModules TYPE CXX_MODULES FILES ${MODULES})

# Link all necessary libraries
target_link_libraries(
  ${PROJECT_NAME} 
  PRIVATE 
      glm::glm
      glfw
      Vulkan::Vulkan
      OpenGL::GL
      GLEW::GLEW
)

# Include path for internal access
target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if (BUILD_DEMO)
    add_subdirectory(demo)
endif()

# Copy commands for clangd
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()
