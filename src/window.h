#pragma once

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>

#include <array>
#include <functional>

namespace window {

enum class KeyAction {
  Down,
  Up,
  Held,
};

class Window {
 private:
  friend class Manager;

  using ResizeCallback = std::function<void(uint16_t, uint16_t)>;

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

  void on_framebuffer_resize(ResizeCallback callback);

 private:
  GLFWwindow* window;

  std::array<bool, GLFW_KEY_LAST> keys;

  ResizeCallback resize_callback;
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
