#include "gfx/shader.h"

#include <iostream>

namespace gfx {

Shader::Shader(ShaderSources sources) {
  const bgfx::Memory* ref = nullptr;

  switch (bgfx::getRendererType()) {
    case bgfx::RendererType::OpenGLES:
      ref = bgfx::makeRef(sources.essl, sources.essl_size);
      break;
    case bgfx::RendererType::OpenGL:
      ref = bgfx::makeRef(sources.glsl, sources.glsl_size);
      break;
    case bgfx::RendererType::Vulkan:
      ref = bgfx::makeRef(sources.spv, sources.spv_size);
      break;

    default:
      std::cerr << "cannot load shader for renderer type: " << static_cast<int>(bgfx::getRendererType()) << std::endl;
      break;
  }

  handle = bgfx::createShader(ref);
  std::cout << "shader created: " << handle.idx << std::endl;
}

Shader::~Shader() {
  bgfx::destroy(handle);
  std::cout << "shader destroyed: " << handle.idx << std::endl;
}

}  // namespace gfx
