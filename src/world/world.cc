#include "world/world.h"

namespace world {

Chunk& World::get_chunk(ChunkInWorldCoords coords) {
  auto index = (static_cast<uint64_t>(coords.x) << 16) + static_cast<uint64_t>(coords.z);
  return chunks[index];
}

}  // namespace world
