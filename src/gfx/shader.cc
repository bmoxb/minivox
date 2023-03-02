#include "gfx/shader.h"

namespace gfx {

Shader::Shader(const uint8_t* data, uint32_t size)
    : handle(bgfx::createShader(bgfx::makeRef(data, size))) {}

Shader::~Shader() {
  bgfx::destroy(handle);
}

}  // namespace gfx
