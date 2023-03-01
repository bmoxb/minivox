#include "graphics.h"

#include <iostream>

namespace graphics {

Handle::Handle(window::Window& window) {
  bgfx::Init bgfx_init;

  bgfx_init.type = bgfx::RendererType::Count;
  bgfx_init.resolution.width = window.get_framebuffer_width();
  bgfx_init.resolution.height = window.get_framebuffer_height();
  bgfx_init.resolution.reset = BGFX_RESET_VSYNC;
  bgfx_init.platformData = window.get_platform_data();

  if (bgfx::init(bgfx_init)) {
    std::cout << "bgfx initialised" << std::endl;
  } else {
    std::cerr << "bgfx initialisation failed" << std::endl;
  }
}

Handle::~Handle() {
  bgfx::shutdown();
  std::cout << "bgfx shutdown" << std::endl;
}

}  // namespace graphics
