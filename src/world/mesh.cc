#include "world/mesh.h"

#include <bgfx/bgfx.h>

#include "fs.sc.essl.bin.h"
#include "fs.sc.glsl.bin.h"
#include "fs.sc.spv.bin.h"
#include "gfx/program.h"
#include "gfx/shader.h"
#include "vs.sc.essl.bin.h"
#include "vs.sc.glsl.bin.h"
#include "vs.sc.spv.bin.h"

namespace world {

inline bgfx::VertexLayout make_vertex_layout() {
  bgfx::VertexLayout layout;
  layout
      .begin()
      .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
      .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
      .end();
  return layout;
}

static bgfx::VertexLayout vertex_layout = make_vertex_layout();

static gfx::Program& shader_program() {
  static gfx::Program program(gfx::Shader(SHADER_SOURCES(vs)), gfx::Shader(SHADER_SOURCES(fs)));
  return program;
}

Mesh::Mesh(bx::Vec3 pos, std::vector<Vertex> vertex_data, std::vector<uint16_t> index_data)
    : vertices(std::move(vertex_data), vertex_layout), indices(std::move(index_data)) {
  bx::mtxRotateY(transform.data(), 0.0f);
  transform[12] = pos.x;
  transform[13] = pos.y;
  transform[14] = pos.z;
}

void Mesh::draw() const {
  bgfx::setTransform(transform.data());
  vertices.use();
  indices.use();
  shader_program().submit();
}

}  // namespace world
