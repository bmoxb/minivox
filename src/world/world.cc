#include "world/world.h"

#include "fs.sc.essl.bin.h"
#include "fs.sc.glsl.bin.h"
#include "fs.sc.spv.bin.h"
#include "gfx/shader.h"
#include "vs.sc.essl.bin.h"
#include "vs.sc.glsl.bin.h"
#include "vs.sc.spv.bin.h"

namespace world {

World::World() : shader_program(gfx::Shader(SHADER_SOURCES(vs)), gfx::Shader(SHADER_SOURCES(fs))) {
  ChunkInWorldCoords pos{0, 0};
  Chunk chunk(pos, shader_program);
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
