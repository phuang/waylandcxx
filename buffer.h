#ifndef __BUFFER_H_
#define __BUFFER_H_

#include <memory>

#include <wayland-client.h>

#include "proxy.h"

namespace wl {

class BufferPool;

class Buffer : public Proxy<struct wl_buffer, Buffer> {
 public:
  explicit Buffer(struct wl_buffer* buffer);
  ~Buffer();

 private:
  // Event handlers:
  void OnRelease(struct wl_buffer* buffer);

  // Event handler thunks:
  static void OnReleaseThunk(void* data, struct wl_buffer* buffer);

  static const struct wl_buffer_listener listener_;
};

}

#endif
