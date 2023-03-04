#pragma once

#include <cstdint>
#include <functional>

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

  bool operator==(const ChunkInWorldCoords& other) const {
    return (x == other.x) && (z == other.z);
  }
};

}  // namespace world

namespace std {
template <>
struct hash<world::ChunkInWorldCoords> {
  std::size_t operator()(const world::ChunkInWorldCoords& k) const {
    auto combined = (static_cast<uint64_t>(k.x) << 32) + static_cast<uint64_t>(k.z);
    return std::hash<uint64_t>()(combined);
  }
};

}  // namespace std
