#pragma once

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>

#include <functional>

namespace window {

class Window {
 private:
  friend class Manager;

  Window(GLFWwindow* window);

 public:
  ~Window();

  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  bgfx::PlatformData get_platform_data() const;

  uint16_t get_framebuffer_width() const;
  uint16_t get_framebuffer_height() const;

  void close() const;
  bool is_open() const;

  bool is_key_down(int glfw_key) const;

  void on_framebuffer_resize(std::function<void(uint16_t, uint16_t)> callback);

 private:
  GLFWwindow* window;

  std::function<void(uint16_t, uint16_t)> resize_callback;
};

class Manager {
 public:
  Manager();
  ~Manager();

  Manager(const Manager&) = delete;
  Manager& operator=(const Manager&) = delete;

  Window new_window(int width, int height, const char* title) const;
};

};  // namespace window
