#include "world/chunk.h"

#include <vector>

namespace world {

Chunk::Chunk(ChunkInWorldCoords coords, const gfx::Program& program) : chunk_in_word_coords(coords) {
  build_mesh(program);
}

void Chunk::build_mesh(const gfx::Program& program) {
  std::vector<Vertex> vertex_data = {
      {-1.0f, 1.0f, 1.0f, 0xff000000},
      {1.0f, 1.0f, 1.0f, 0xff0000ff},
      {-1.0f, -1.0f, 1.0f, 0xff00ff00},
      {1.0f, -1.0f, 1.0f, 0xff00ffff},
      {-1.0f, 1.0f, -1.0f, 0xffff0000},
      {1.0f, 1.0f, -1.0f, 0xffff00ff},
      {-1.0f, -1.0f, -1.0f, 0xffffff00},
      {1.0f, -1.0f, -1.0f, 0xffffffff},
  };
  std::vector<uint16_t> index_data = {
      0, 1, 2, 1, 3, 2,  //
      4, 6, 5, 5, 6, 7,  //
      0, 2, 4, 4, 2, 6,  //
      1, 5, 3, 5, 7, 3,  //
      0, 4, 1, 4, 5, 1,  //
      2, 3, 6, 6, 3, 7,  //
  };

  bx::Vec3 world_pos{
      static_cast<float>(chunk_in_word_coords.x) * static_cast<float>(CHUNK_WIDTH),
      0.0f,
      static_cast<float>(chunk_in_word_coords.z) * static_cast<float>(CHUNK_WIDTH),
  };

  mesh = std::make_unique<Mesh>(program, world_pos, std::move(vertex_data), std::move(index_data));
}

void Chunk::draw() const {
  if (mesh) {
    mesh->draw();
  }
}

Voxel Chunk::get(VoxelInChunkCoords coords) const {
  auto index = (static_cast<std::size_t>(coords.x) * CHUNK_WIDTH * CHUNK_WIDTH) +
               (static_cast<std::size_t>(coords.y) * CHUNK_WIDTH) +
               static_cast<std::size_t>(coords.z);

  return voxels[index];
}

}  // namespace world
