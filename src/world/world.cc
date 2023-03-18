#include "world/world.h"

namespace world {

World::World() {
  ChunkInWorldCoords pos{0, 0};
  Chunk chunk(pos);
  chunks.emplace(pos, std::move(chunk));
}

void World::draw() const {
  for (const auto& it : chunks) {
    const Chunk& chunk = it.second;
    chunk.draw();
  }
}

Chunk& World::get_chunk(ChunkInWorldCoords coords) {
  return chunks.at(coords);
}

}  // namespace world
