#ifndef __REGISTRY_H_
#define __REGISTRY_H_

#include <wayland-client.h>

#include "proxy.h"
#include "surface.h"

namespace wl {

class Surface;

class Registry : public Proxy<struct wl_registry, Registry> {
 public:
  class Delegate {
   public:
    virtual void OnGlobal(
        uint32_t id, const char* interface, uint32_t version) {}
    virtual void OnGlobalRemove(uint32_t id) {}
  };

  explicit Registry(struct wl_registry* registry,
                    Delegate* delegate);
  ~Registry();

  template<typename T>
  T* Bind(uint32_t name, const struct wl_interface* interface,
          uint32_t version) {
    void* ret = wl_registry_bind(id(), name, interface, version);
    return static_cast<T*>(ret);
  }

 private:
  // Event handlers:
  void OnGlobal(struct wl_registry* registry, uint32_t id,
                const char* interface, uint32_t version);
  void OnGlobalRemove(struct wl_registry* registry, uint32_t id);

  // Event handler thunks:
  static void OnGlobalThunk(void* data,
                            struct wl_registry* registry,
                            uint32_t id,
                            const char* interface,
                            uint32_t version);
  static void OnGlobalRemoveThunk(void* data,
                                  struct wl_registry* registry,
                                  uint32_t id);

  Delegate* delegate_;

  static const struct wl_registry_listener listener_;
};

}  // namespace wl


#endif
