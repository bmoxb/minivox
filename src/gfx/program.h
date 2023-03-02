#pragma once

#include <bgfx/bgfx.h>

#include "gfx/shader.h"

namespace gfx {

class Program {
 public:
  Program(const Shader& vert, const Shader& frag);
  ~Program();

  void submit() const;

  Program(const Program&) = delete;
  Program& operator=(const Program&) = delete;

 private:
  bgfx::ProgramHandle handle;
};

}  // namespace gfx
