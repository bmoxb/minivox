#include "util/window.h"

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

#include <iostream>

namespace util {

// Initialise GLFW and create a GLFW window.
inline GLFWwindow* glfw_init(const std::string& title, uint16_t width, uint16_t height) {
  if (glfwInit()) {
    std::cout << "GLFW initialised" << std::endl;
  } else {
    std::cerr << "GLFW initialisation failed" << std::endl;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  auto raw_window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr, nullptr);

  if (raw_window) {
    std::cout << "window created" << std::endl;
  } else {
    std::cerr << "failed to create GLFW window" << std::endl;
  }

  return raw_window;
}

// Initialise bfgx such that it will draw to the given GLFW window.
inline void bgfx_init(GLFWwindow* raw_window) {
  bgfx::Init bgfx_init;

  int width, height;
  glfwGetFramebufferSize(raw_window, &width, &height);

  bgfx_init.type = bgfx::RendererType::Count;
  bgfx_init.resolution.width = static_cast<uint32_t>(width);
  bgfx_init.resolution.height = static_cast<uint32_t>(height);
  bgfx_init.resolution.reset = BGFX_RESET_VSYNC;

  // TODO: Handle other platforms.
  bgfx_init.platformData.ndt = glfwGetX11Display();
  bgfx_init.platformData.nwh = reinterpret_cast<void*>(glfwGetX11Window(raw_window));

  if (bgfx::init(bgfx_init)) {
    std::cout << "bgfx initialised" << std::endl;
  } else {
    std::cerr << "bgfx initialisation failed" << std::endl;
  }

  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000FF);
  bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(width), static_cast<uint16_t>(height));
}

Window::Window(const std::string& title, uint16_t width, uint16_t height)
    : raw_window(glfw_init(title, width, height)) {
  bgfx_init(raw_window);

  // allow our wrapper window to be accessed from callback functions
  glfwSetWindowUserPointer(raw_window, reinterpret_cast<void*>(this));

  // handle key presses
  glfwSetKeyCallback(raw_window, [](GLFWwindow* w, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods) {
    auto self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(w));

    auto index = static_cast<std::size_t>(key);

    switch (action) {
      case GLFW_PRESS:
        self->pressed_keys[index] = true;
        self->held_keys[index] = true;
        break;

      case GLFW_RELEASE:
        self->held_keys[index] = false;
        break;
    }
  });

  // handle the framebuffer (part of window that is drawn to) being resized
  glfwSetFramebufferSizeCallback(raw_window, [](GLFWwindow* w, int new_width, int new_height) {
    auto self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(w));

    FramebufferSize size{
        .width = static_cast<uint16_t>(new_width),
        .height = static_cast<uint16_t>(new_height),
    };
    self->new_size = std::make_optional(size);
  });
}

Window::~Window() {
  bgfx::shutdown();
  std::cout << "bgfx terminated" << std::endl;

  glfwDestroyWindow(raw_window);
  std::cout << "window destroyed" << std::endl;

  glfwTerminate();
  std::cout << "GLFW terminated" << std::endl;
}

void Window::close() const {
  glfwSetWindowShouldClose(raw_window, GLFW_TRUE);
}

bool Window::is_open() const {
  return glfwWindowShouldClose(raw_window) == GLFW_FALSE;
}

bool Window::was_key_pressed(int glfw_key) {
  auto index = static_cast<std::size_t>(glfw_key);
  bool pressed = pressed_keys[index];
  pressed_keys[index] = false;
  return pressed;
}

bool Window::is_key_down(int glfw_key) const {
  return held_keys[static_cast<std::size_t>(glfw_key)];
}

std::optional<FramebufferSize> Window::framebuffer_size_change() {
  auto size = new_size;
  new_size = std::nullopt;
  return size;
}

};  // namespace util
