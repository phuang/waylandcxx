#include "shm_pool.h"

#include "buffer.h"

namespace wl {

ShmPool::ShmPool(struct wl_shm_pool* shm_pool) : Proxy(shm_pool) {}

ShmPool::~ShmPool() { wl_shm_pool_destroy(id()); }

std::unique_ptr<Buffer> ShmPool::CreateBuffer(Buffer::Delegate* delegate,
                                              int32_t offset, int32_t width,
                                              int32_t height, int32_t stride,
                                              uint32_t format) {
  auto buffer =
      wl_shm_pool_create_buffer(id(), offset, width, height, stride, format);
  if (!buffer) return nullptr;
  return std::unique_ptr<Buffer>(new Buffer(buffer, delegate));
}

void ShmPool::Resize(int32_t size) { wl_shm_pool_resize(id(), size); }

}  // namespace wl
