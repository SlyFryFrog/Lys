cmake_minimum_required(VERSION 3.30)
project(Lys LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD ON)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE MODULES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm)

# option(COPY_RESOURCES "Enable copying resource files to the build directory" ON)
# option(ENABLE_VENDOR_LIBS "Enable building vendor libraries" ON)

# find_package(<insert> REQUIRED)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/<insert>)

# add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

add_executable(${PROJECT_NAME} ${SOURCES} ${MODULES})
target_sources(${PROJECT_NAME} PUBLIC FILE_SET allModules TYPE CXX_MODULES FILES ${MODULES})
# target_link_libraries(
#   ${INSERT_PROJECT_NAME} 
#   PRIVATE 
#       PACKAGE_0 
#       PACKAGE_1
# )

# target_include_directories(
#     ${PROJECT_NAME} 
#     PRIVATE 
#         ${CMAKE_CURRENT_SOURCE_DIR}/src
# )

# # Copy resource files to build dir
# if (COPY_RESOURCES)
#     file(GLOB RSC_FILES "${CMAKE_SOURCE_DIR}/rsc/*")
#     foreach(file ${RSC_FILES})
#         file(COPY ${file} DESTINATION ${CMAKE_BINARY_DIR}/rsc/)
#     endforeach()
# endif()


# Copy commands for clangd
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()