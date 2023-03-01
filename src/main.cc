#include <bgfx/bgfx.h>

#include <iostream>

#include "window.h"

int main(int argc, char* argv[]) {
  window::Manager window_manager;

  auto window = window_manager.new_window();

  bgfx::Init bgfx_init;
  bgfx_init.type = bgfx::RendererType::Count;
  bgfx_init.resolution.width = 1280;
  bgfx_init.resolution.height = 720;
  bgfx_init.resolution.reset = BGFX_RESET_VSYNC;
  bgfx_init.platformData = window.get_platform_data();

  bgfx::init(bgfx_init);

  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xFF0000FF, 1.0f, 0);
  bgfx::setViewRect(0, 0, 0, 1280, 720);

  while (window.is_open()) {
    bgfx::touch(0);
    bgfx::frame();

    glfwPollEvents();

    if (window.is_key_down(GLFW_KEY_ESCAPE)) {
      window.close();
    }
  }

  bgfx::shutdown();

  return EXIT_SUCCESS;
}
