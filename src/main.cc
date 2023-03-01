#include <bgfx/bgfx.h>

#include <iostream>

#include "window.h"

int main() {
  window::Window window("minivox", 800, 600);

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
