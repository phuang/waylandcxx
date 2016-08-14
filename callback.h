#ifndef __CALLBACK_H_
#define __CALLBACK_H_

#include <wayland-client.h>

#include "proxy.h"

namespace wl {

class Callback : public Proxy<struct wl_callback, Callback> {
 public:
  Callback(struct wl_callback* callback);
  ~Callback();

  // Event handlers:
  virtual void OnDone(struct wl_callback* callback,
                      uint32_t callback_data);

 private:
  // Event handler thunks:
  static void OnDoneThunk(void* data,
                          struct wl_callback* callback,
                          uint32_t callback_data);

  static const struct wl_callback_listener listener_;
};

}  // namespace wl
#endif
