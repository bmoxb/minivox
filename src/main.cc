#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <bgfx/bgfx.h>

#include <iostream>

int main(int argc, char* argv[]) {
  if (!glfwInit()) {
    std::cerr << "GLFW initialisation failed" << std::endl;
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  auto window = glfwCreateWindow(1280, 720, "minivox", nullptr, nullptr);
  if (!window) {
    std::cerr << "failed to create GLFW window" << std::endl;
    return EXIT_FAILURE;
  }

  bgfx::Init bgfx_init;
  bgfx_init.type = bgfx::RendererType::Count;
  bgfx_init.resolution.width = 1280;
  bgfx_init.resolution.height = 720;
  bgfx_init.resolution.reset = BGFX_RESET_VSYNC;

  bgfx_init.platformData.ndt = glfwGetX11Display();
  bgfx_init.platformData.nwh = reinterpret_cast<void*>(glfwGetX11Window(window));

  bgfx::init(bgfx_init);

  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xFF0000FF, 1.0f, 0);
  bgfx::setViewRect(0, 0, 0, 1280, 720);

  while (!glfwWindowShouldClose(window)) {
    bgfx::touch(0);
    bgfx::frame();

    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }
  }

  bgfx::shutdown();

  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}
