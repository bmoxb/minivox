#pragma once

#include <array>
#include <cstdint>

#include "world/coords.h"
#include "world/voxel.h"

namespace world {

constexpr std::size_t CHUNK_WIDTH = 32, CHUNK_HEIGHT = 256;
constexpr std::size_t CHUNK_VOXEL_COUNT = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;

class Chunk {
 public:
  Chunk() = default;

  Chunk(const Chunk&) = delete;
  Chunk& operator=(const Chunk&) = delete;

  void draw(const ChunkInWorldCoords& coords) const;

 private:
  Voxel get(VoxelInChunkCoords coords) const;

  std::array<Voxel, CHUNK_VOXEL_COUNT> voxels;
};

}  // namespace world
