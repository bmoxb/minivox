cmake_minimum_required(VERSION 3.11)
project(minivox LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)# -Werror)

add_subdirectory(bgfx.cmake/)
include_directories(bgfx.cmake/bgfx/include/)

add_subdirectory(glfw/)
include_directories(glfw/include/)

file(GLOB_RECURSE SRC_FILES src/*.cc)
include_directories(src)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} bgfx glfw)
