cmake_minimum_required(VERSION 4.0)
project(Lys LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE MODULES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm)

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
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

# Copy commands for clangd
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()