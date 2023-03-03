cmake_minimum_required(VERSION 3.11)
project(minivox LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(bgfx.cmake/)
include_directories(SYSTEM bgfx.cmake/bgfx/include/ bgfx.cmake/bx/include/)
set(BGFX_SHADER_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/bgfx.cmake/bgfx/src)

add_subdirectory(shaders/)
include_directories(${CMAKE_BINARY_DIR}/compiled_shaders/)

add_subdirectory(glfw/)
include_directories(SYSTEM glfw/include/)

file(GLOB_RECURSE SRC_FILES src/*.cc)
include_directories(src/)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    -pedantic -Wall -Wextra -Werror -Wconversion -Wcast-qual -Wlogical-op
    -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast
    -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion
    -Wsign-promo -Wstrict-null-sentinel -Wundef
)

target_link_libraries(${PROJECT_NAME} shaders bgfx glfw)
