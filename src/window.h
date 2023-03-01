#pragma once

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>

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

  void close() const;
  bool is_open() const;

  bool is_key_down(int glfw_key) const;

 private:
  GLFWwindow* window;
};

class Manager {
 public:
  Manager();
  ~Manager();

  Manager(const Manager&) = delete;
  Manager& operator=(const Manager&) = delete;

  Window new_window() const;
};

};  // namespace window
