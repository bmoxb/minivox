#include "gfx/indexbuffer.h"

namespace gfx {

IndexBuffer::IndexBuffer(std::vector<uint16_t> index_data)
    : data(std::move(index_data)),
      handle(bgfx::createIndexBuffer(bgfx::makeRef(&data.front(), sizeof(uint16_t) * data.size()))) {}

IndexBuffer::~IndexBuffer() {
  bgfx::destroy(handle);
}

void IndexBuffer::use() const {
  bgfx::setIndexBuffer(handle);
}

}  // namespace gfx
