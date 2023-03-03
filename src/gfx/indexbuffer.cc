#include "gfx/indexbuffer.h"

#include "gfx/buffer.h"

namespace gfx {

IndexBuffer::IndexBuffer(std::vector<uint16_t> index_data)
    : data(std::move(index_data)),
      handle(bgfx::createIndexBuffer(make_data_ref(data))) {}

IndexBuffer::~IndexBuffer() {
  bgfx::destroy(handle);
}

void IndexBuffer::use() const {
  bgfx::setIndexBuffer(handle);
}

}  // namespace gfx
