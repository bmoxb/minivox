#pragma once

#include <bgfx/bgfx.h>

#include <vector>

#include "gfx/buffer.h"

namespace gfx {

template <class T>
class VertexBuffer {
 public:
  VertexBuffer(std::vector<T> vertex_data, const bgfx::VertexLayout& layout)
      : data(std::move(vertex_data)),
        handle(bgfx::createVertexBuffer(make_data_ref(data), layout)) {}

  ~VertexBuffer() {
    bgfx::destroy(handle);
  }

  void use() const {
    bgfx::setVertexBuffer(0, handle);
  }

 private:
  const std::vector<T> data;
  const bgfx::VertexBufferHandle handle;
};

}  // namespace gfx
