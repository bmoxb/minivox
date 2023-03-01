#include "window.h"

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

#include <iostream>

namespace window {

Window::Window(GLFWwindow* window) : window(window) {
  glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));

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

uint16_t Window::get_framebuffer_width() const {
  int width;
  glfwGetFramebufferSize(window, &width, nullptr);
  return static_cast<uint16_t>(width);
}

uint16_t Window::get_framebuffer_height() const {
  int height;
  glfwGetFramebufferSize(window, nullptr, &height);
  return static_cast<uint16_t>(height);
}

void Window::close() const {
  glfwSetWindowShouldClose(window, GLFW_TRUE);
}

bool Window::is_open() const {
  return glfwWindowShouldClose(window) == GLFW_FALSE;
}

void Window::on_key(KeyCallback callback) {
  key_callback = callback;

  glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int _scancode, int glfw_action, int _mods) {
    KeyAction action;
    switch (glfw_action) {
      case GLFW_PRESS:
        action = KeyAction::Down;
        break;
      case GLFW_RELEASE:
        action = KeyAction::Up;
        break;
      case GLFW_REPEAT:
        action = KeyAction::Held;
        break;
    }

    auto self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
    self->key_callback(action, key);
  });
}

void Window::on_framebuffer_resize(ResizeCallback callback) {
  resize_callback = callback;

  glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int width, int height) {
    auto self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
    self->resize_callback(static_cast<uint16_t>(width), static_cast<uint16_t>(height));
  });
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

Window Manager::new_window(int width, int height, const char* title) const {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  auto raw_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

  if (!raw_window) {
    std::cerr << "failed to create GLFW window" << std::endl;
  }

  return Window(raw_window);
}

};  // namespace window
