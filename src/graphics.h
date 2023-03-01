#pragma once

#include <bgfx/bgfx.h>

#include "window.h"

namespace graphics {

class Handle {
 public:
  Handle(window::Window& window);
  ~Handle();

  Handle(const Handle&) = delete;
  Handle& operator=(const Handle&) = delete;
};

}  // namespace graphics
