project(Demo)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE MODULES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm)

if (LYS_CUSTOM_MAIN)
    add_executable(${PROJECT_NAME} ${SOURCES})
    
    target_link_libraries(
        ${PROJECT_NAME} 
        PRIVATE 
            Lys
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
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/scripts)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
