#include "world/world.h"

namespace world {

void World::draw() const {
  for (const auto& it : chunks) {
    const ChunkInWorldCoords& coords = it.first;
    const Chunk& chunk = it.second;

    chunk.draw(coords);
  }
}

Chunk& World::get_chunk(ChunkInWorldCoords coords) {
  return chunks[coords];
}

}  // namespace world
