#pragma once

#include <cstdint>
#include <unordered_map>

#include "world/chunk.h"
#include "world/coords.h"

namespace world {

class World {
 public:
  World();

  World(const World&) = delete;
  World& operator=(const World&) = delete;

  void draw() const;

 private:
  Chunk& get_chunk(ChunkInWorldCoords coords);

  std::unordered_map<ChunkInWorldCoords, Chunk> chunks;
};

}  // namespace world
