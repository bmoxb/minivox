#include "gfx/program.h"

#include <iostream>

namespace gfx {

Program::Program(const Shader& vert, const Shader& frag)
    : handle(bgfx::createProgram(vert.handle, frag.handle)) {
  std::cout << "program created: " << handle.idx << std::endl;
}

Program::~Program() {
  bgfx::destroy(handle);
  std::cout << "program destroyed: " << handle.idx << std::endl;
}

void Program::submit() const {
  bgfx::submit(0, handle);
}

}  // namespace gfx
