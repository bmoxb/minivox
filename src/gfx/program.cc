#include "gfx/program.h"

namespace gfx {

Program::Program(const Shader& vert, const Shader& frag)
    : handle(bgfx::createProgram(vert.handle, frag.handle)) {}

Program::~Program() {
  bgfx::destroy(handle);
}

void Program::submit() const {
  bgfx::submit(0, handle);
}

}  // namespace gfx
