#include "util/debug.h"

#include <bgfx/bgfx.h>

namespace util {

void Debug::toggle_wireframe() {
  wireframe = !wireframe;
  update();
}

void Debug::toggle_stats() {
  stats = !stats;
  update();
}

void Debug::update() const {
  bgfx::setDebug((wireframe ? BGFX_DEBUG_WIREFRAME : 0) | (stats ? BGFX_DEBUG_STATS : 0));
}

}  // namespace util
