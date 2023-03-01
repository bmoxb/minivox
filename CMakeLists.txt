cmake_minimum_required(VERSION 3.11)
project(minivox LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(bgfx.cmake/)
include_directories(bgfx.cmake/bgfx/include/)
set(BGFX_SHADER_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/bgfx.cmake/bgfx/src)

add_subdirectory(shaders/)
include_directories(${CMAKE_BINARY_DIR}/compiled_shaders/)

add_subdirectory(glfw/)
include_directories(glfw/include/)

file(GLOB_RECURSE SRC_FILES src/*.cc)
include_directories(src/)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

target_link_libraries(${PROJECT_NAME} shaders bgfx glfw)
