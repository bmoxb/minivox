#include <bgfx/bgfx.h>

#include <iostream>

#include "graphics.h"
#include "window.h"

int main() {
  window::Manager window_manager;

  auto window = window_manager.new_window(800, 600, "minivox");

  graphics::Handle bgfx_handle(window);

  window.on_framebuffer_resize([](uint16_t width, uint16_t height) {
    std::cout << "framebuffer resized: " << width << ", " << height << std::endl;

    bgfx::setViewRect(0, 0, 0, width, height);
  });

  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xFF0000FF, 1.0f, 0);
  bgfx::setViewRect(0, 0, 0, window.get_framebuffer_width(), window.get_framebuffer_height());

  while (window.is_open()) {
    bgfx::touch(0);
    bgfx::frame();

    glfwPollEvents();

    if (window.is_key_down(GLFW_KEY_ESCAPE)) {
      window.close();
    }
  }

  return EXIT_SUCCESS;
}
