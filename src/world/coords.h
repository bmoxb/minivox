#pragma once

#include <cstdint>

namespace world {

struct VoxelInWorldCoords {
  uint32_t x;
  uint8_t y;
  uint32_t z;
};

struct VoxelInChunkCoords {
  uint8_t x;
  uint8_t y;
  uint8_t z;
};

struct ChunkInWorldCoords {
  uint32_t x;
  uint32_t z;
};

}  // namespace world
