project(Demo)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE MODULES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

if (LYS_CUSTOM_MAIN)
    add_executable(${PROJECT_NAME} ${SOURCES})
    
    target_link_libraries(
        ${PROJECT_NAME} 
        PRIVATE 
            Lys
            GLEW::GLEW
            OpenGL::GL
    )
else()
    # TODO - Do nothing for now
    foreach(source_file ${SOURCES})
        if(source_file MATCHES "main.cpp")
            list(REMOVE_ITEM SOURCES ${source_file})
        endif()
    endforeach()

    add_library(${PROJECT_NAME} SHARED ${SOURCES})
    
    target_link_libraries(
        Lys
        PRIVATE
            ${PROJECT_NAME}
    )
endif()

target_sources(${PROJECT_NAME} PUBLIC FILE_SET allModules TYPE CXX_MODULES FILES ${MODULES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# If in debug mode, create symlinks of all resource files to enable hot-reloading capabilities.
# For release/distribution builds, it should create shallow copies (new copies).
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    foreach(dir shaders rsc scripts)
        add_custom_command(
                TARGET Demo POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:Demo>/${dir}
                COMMAND ${CMAKE_COMMAND} -E create_symlink
                ${CMAKE_CURRENT_SOURCE_DIR}/${dir}
                $<TARGET_FILE_DIR:Demo>/${dir}
                COMMENT "Symlinking ./demo/${dir} -> build/Debug/demo/${dir}"
        )
    endforeach()
else()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/rsc DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/scripts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()