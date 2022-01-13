cmake_minimum_required(VERSION 3.13)
project(app LANGUAGES CXX C)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/glfw)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/stb_image)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/glm)

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Screen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vec.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Polygon.cpp
    )

target_include_directories(
    ${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

target_link_libraries(
    ${PROJECT_NAME} glad glfw GL dl stb_image glm
    )