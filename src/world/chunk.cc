#include "world/chunk.h"

namespace world {

Voxel Chunk::get(VoxelInChunkCoords coords) const {
  auto index = (static_cast<std::size_t>(coords.x) * CHUNK_WIDTH * CHUNK_WIDTH) +
               (static_cast<std::size_t>(coords.y) * CHUNK_WIDTH) +
               static_cast<std::size_t>(coords.z);

  return voxels[index];
}

}  // namespace world
