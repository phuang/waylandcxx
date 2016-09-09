#include "shm.h"

#include "shm_pool.h"

namespace wl {

const struct wl_shm_listener Shm::listener_ = {
    Shm::OnFormatThunk,
};

Shm::Shm(struct wl_shm* shm) : Proxy(shm) {
  wl_shm_add_listener(id(), &listener_, this);
}

Shm::~Shm() { wl_shm_destroy(id()); }

std::unique_ptr<ShmPool> Shm::CreatePool(int32_t fd, int32_t size) {
  auto shm = wl_shm_create_pool(id(), fd, size);
  if (!shm) return nullptr;
  return std::unique_ptr<ShmPool>(new ShmPool(shm));
}

void Shm::OnFormat(struct wl_shm* shm, uint32_t format) {
  fprintf(stderr, "%s format=0x%08x\n", __func__, format);
  formats_.insert(static_cast<enum wl_shm_format>(format));
}

// static
void Shm::OnFormatThunk(void* data, struct wl_shm* shm, uint32_t format) {
  static_cast<Shm*>(data)->OnFormat(shm, format);
}

}  // namespace wl
