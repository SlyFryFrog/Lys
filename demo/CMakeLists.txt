project(Demo)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE MODULES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm)

add_executable(${PROJECT_NAME} ${SOURCES})
target_sources(${PROJECT_NAME} PUBLIC FILE_SET allModules TYPE CXX_MODULES FILES ${MODULES})

target_link_libraries(
    Demo 
    PRIVATE 
        Lys
)