#pragma once

#include <bgfx/bgfx.h>

#include "gfx/shader.h"

namespace gfx {

class Program {
 public:
  Program(const Shader& vert, const Shader& frag);
  ~Program();

  Program(const Program&) = delete;
  Program& operator=(const Program&) = delete;

  void submit() const;

 private:
  bgfx::ProgramHandle handle;
};

}  // namespace gfx
