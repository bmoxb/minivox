#pragma once

#include <bgfx/bgfx.h>

#include <vector>

namespace gfx {

class IndexBuffer {
 public:
  IndexBuffer(std::vector<uint16_t> index_data);
  ~IndexBuffer();

  IndexBuffer(const IndexBuffer&) = delete;
  IndexBuffer& operator=(const IndexBuffer&) = delete;

  void use() const;

 private:
  const std::vector<uint16_t> data;
  const bgfx::IndexBufferHandle handle;
};

}  // namespace gfx
