#pragma once

#include <bgfx/bgfx.h>

#include <vector>

namespace gfx {
template <typename T>
inline const bgfx::Memory* make_data_ref(const std::vector<T>& data) {
  return bgfx::makeRef(&data.front(), sizeof(T) * data.size());
}
}  // namespace gfx
