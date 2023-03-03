#pragma once

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>

#include <array>
#include <optional>
#include <string>

namespace util {

struct FramebufferSize {
  uint16_t width;
  uint16_t height;
};

class Window {
 public:
  /*
   * Initialise GLFW, create a GLFW window, and initialise bfgx such that that window may be drawn to.
   */
  Window(const std::string& title, uint16_t width, uint16_t height);

  ~Window();

  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  void close() const;
  bool is_open() const;

  bool is_key_down(int glfw_key) const;

  std::optional<FramebufferSize> framebuffer_size_change();

 private:
  GLFWwindow* raw_window;

  std::array<bool, GLFW_KEY_LAST> keys;

  std::optional<FramebufferSize> new_size;
};

};  // namespace util
