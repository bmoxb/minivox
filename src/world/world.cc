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
  ChunkInWorldCoords pos_0{0, 0};
  Chunk chunk_0(pos_0, shader_program);
  chunks.emplace(pos_0, std::move(chunk_0));
  ChunkInWorldCoords pos_1{0, -1};
  Chunk chunk_1(pos_1, shader_program);
  chunks.emplace(pos_1, std::move(chunk_1));
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
