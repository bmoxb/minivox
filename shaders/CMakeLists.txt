
add_executable(bgfx::shaderc ALIAS shaderc)

set(SHADER_FIES "")

foreach(shader vs)
    set(shader_file ${CMAKE_CURRENT_SOURCE_DIR}/${shader}.sc)
    list(APPEND SHADER_FILES ${shader_file})
    bgfx_compile_shader_to_header(
        TYPE VERTEX
        SHADERS ${shader_file}
        VARYING_DEF ${CMAKE_CURRENT_SOURCE_DIR}/varying.def.sc
        OUTPUT_DIR ${CMAKE_BINARY_DIR}/compiled_shaders
    )
endforeach()

foreach(shader fs)
    set(shader_file ${CMAKE_CURRENT_SOURCE_DIR}/${shader}.sc)
    list(APPEND SHADER_FILES ${shader_file})
    bgfx_compile_shader_to_header(
        TYPE FRAGMENT
        SHADERS ${shader_file}
        VARYING_DEF ${CMAKE_CURRENT_SOURCE_DIR}/varying.def.sc
        OUTPUT_DIR ${CMAKE_BINARY_DIR}/compiled_shaders
    )
endforeach()

add_library(shaders INTERFACE ${SHADER_FILES})
