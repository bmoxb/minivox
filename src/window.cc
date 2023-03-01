#include "window.h"

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

#include <iostream>

namespace window {

Window::Window(GLFWwindow* window) : window(window) {
  std::cout << "window created: " << window << std::endl;
}

Window::~Window() {
  glfwDestroyWindow(window);
  std::cout << "window destroyed: " << window << std::endl;
}

bgfx::PlatformData Window::get_platform_data() const {
  // TODO: Handle other platforms.
  bgfx::PlatformData pd;
  pd.ndt = glfwGetX11Display();
  pd.nwh = reinterpret_cast<void*>(glfwGetX11Window(window));
  return pd;
}

void Window::close() const {
  glfwSetWindowShouldClose(window, GLFW_TRUE);
}

bool Window::is_open() const {
  return glfwWindowShouldClose(window) == GLFW_FALSE;
}

bool Window::is_key_down(int glfw_key) const {
  return glfwGetKey(window, glfw_key) == GLFW_PRESS;
}

Manager::Manager() {
  if (glfwInit()) {
    std::cout << "GLFW initialised" << std::endl;
  } else {
    std::cerr << "GLFW initialisation failed" << std::endl;
  }
}

Manager::~Manager() {
  glfwTerminate();
  std::cout << "GLFW terminated" << std::endl;
}

Window Manager::new_window() const {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  auto raw_window = glfwCreateWindow(1280, 720, "minivox", nullptr, nullptr);

  if (!raw_window) {
    std::cerr << "failed to create GLFW window" << std::endl;
  }

  return Window(raw_window);
}

};  // namespace window
