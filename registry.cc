#include "registry.h"

namespace wl {

const struct wl_registry_listener Registry::listener_ = {
    Registry::OnGlobalThunk, Registry::OnGlobalRemoveThunk,
};

Registry::Registry(struct wl_registry* registry, Delegate* delegate)
    : Proxy(registry), delegate_(delegate) {
  wl_registry_add_listener(id(), &listener_, this);
}

Registry::~Registry() { wl_registry_destroy(id()); }

void Registry::OnGlobal(struct wl_registry* registry, uint32_t id,
                        const char* interface, uint32_t version) {
  if (delegate_) delegate_->OnGlobal(id, interface, version);
}

void Registry::OnGlobalRemove(struct wl_registry* registry, uint32_t id) {
  if (delegate_) delegate_->OnGlobalRemove(id);
}

// static
void Registry::OnGlobalThunk(void* data, struct wl_registry* registry,
                             uint32_t id, const char* interface,
                             uint32_t version) {
  static_cast<Registry*>(data)->OnGlobal(registry, id, interface, version);
}

// static
void Registry::OnGlobalRemoveThunk(void* data, struct wl_registry* registry,
                                   uint32_t id) {
  static_cast<Registry*>(data)->OnGlobalRemove(registry, id);
}

}  // namespace wl
