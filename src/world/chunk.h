#pragma once

#include <array>
#include <cstdint>
#include <memory>

#include "world/coords.h"
#include "world/mesh.h"
#include "world/voxel.h"

namespace world {

constexpr std::size_t CHUNK_WIDTH = 32, CHUNK_HEIGHT = 256;
constexpr std::size_t CHUNK_VOXEL_COUNT = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;

class Chunk {
 public:
  Chunk(ChunkInWorldCoords coords);

  Chunk(const Chunk&) = delete;
  Chunk& operator=(const Chunk&) = delete;

  Chunk(Chunk&&) = default;
  Chunk& operator=(Chunk&&) = default;

  void build_mesh();

  void draw() const;

 private:
  Voxel get(VoxelInChunkCoords coords) const;

  ChunkInWorldCoords chunk_in_word_coords;
  std::array<Voxel, CHUNK_VOXEL_COUNT> voxels;
  std::unique_ptr<Mesh> mesh;
};

}  // namespace world
