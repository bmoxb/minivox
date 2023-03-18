#pragma once

#include <bx/math.h>

#include <array>

#include "gfx/indexbuffer.h"
#include "gfx/vertexbuffer.h"

namespace world {

struct Vertex {
  float x;
  float y;
  float z;
  uint32_t colour;
};

class Mesh {
 public:
  Mesh(bx::Vec3 pos, std::vector<Vertex> vertex_data, std::vector<uint16_t> index_data);

  void draw() const;

 private:
  gfx::VertexBuffer<Vertex> vertices;
  gfx::IndexBuffer indices;
  std::array<float, 16> transform;
};

}  // namespace world
