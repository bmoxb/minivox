#pragma once

#include <bgfx/bgfx.h>

namespace gfx {

class Shader {
 public:
  friend class Program;  // allow Program to access our underlying bgfx::ShaderHandle

  Shader(const uint8_t* data, uint32_t size);
  ~Shader();

  Shader(const Shader&) = delete;
  Shader& operator=(const Shader&) = delete;

 private:
  bgfx::ShaderHandle handle;
};

}  // namespace gfx
