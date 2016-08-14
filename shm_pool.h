#ifndef __SHM_POOL_H_
#define __SHM_POOL_H_

#include <memory>

#include <wayland-client.h>

#include "proxy.h"

namespace wayland {

class Buffer;

class ShmPool : public Proxy<struct wl_shm_pool, ShmPool> {
 public:
  explicit ShmPool(struct wl_shm_pool* shm_pool);
  ~ShmPool();

  std::unique_ptr<Buffer> CreateBuffer(int32_t offset,
                                       int32_t width,
                                       int32_t height,
                                       int32_t stride,
                                       uint32_t format);
  void Resize(int32_t size);

 private:
};

}

#endif
