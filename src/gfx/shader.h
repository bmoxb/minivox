#pragma once

#include <bgfx/bgfx.h>

#define SHADER_SOURCES(NAME)                               \
  gfx::ShaderSources {                                     \
    .essl = NAME##_essl, .essl_size = sizeof(NAME##_essl), \
    .glsl = NAME##_glsl, .glsl_size = sizeof(NAME##_glsl), \
    .spv = NAME##_spv, .spv_size = sizeof(NAME##_spv),     \
  }

namespace gfx {

struct ShaderSources {
  const uint8_t* essl;
  const uint32_t essl_size;
  const uint8_t* glsl;
  const uint32_t glsl_size;
  const uint8_t* spv;
  const uint32_t spv_size;
};

class Shader {
 public:
  friend class Program;  // allow Program to access our underlying bgfx::ShaderHandle

  Shader(ShaderSources sources);
  ~Shader();

  Shader(const Shader&) = delete;
  Shader& operator=(const Shader&) = delete;

 private:
  bgfx::ShaderHandle handle;
};

}  // namespace gfx
