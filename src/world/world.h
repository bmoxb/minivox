#pragma once

#include <cstdint>
#include <unordered_map>

#include "world/chunk.h"
#include "world/coords.h"

namespace world {

class World {
 public:
  World() = default;

  World(const World&) = delete;
  World& operator=(const World&) = delete;

 private:
  Chunk& get_chunk(ChunkInWorldCoords coords);

  std::unordered_map<uint64_t, Chunk> chunks;
};

}  // namespace world
