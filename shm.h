#ifndef __SHM_H_
#define __SHM_H_

#include <memory>
#include <set>

#include <wayland-client.h>

#include "proxy.h"

namespace wl {

class ShmPool;

class Shm : public Proxy<struct wl_shm, Shm> {
 public:
  explicit Shm(struct wl_shm* shm);
  ~Shm();

  std::unique_ptr<ShmPool> CreatePool(int32_t fd, int32_t size);

 private:
  // Event handlers:
  void OnFormat(struct wl_shm* shm, uint32_t format);

  // Event handler thunks:
  static void OnFormatThunk(void* data, struct wl_shm* shm, uint32_t format);

  // Supported formats.
  std::set<enum wl_shm_format> formats_;

  static const struct wl_shm_listener listener_;

};

}

#endif
