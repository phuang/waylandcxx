#include "buffer.h"

namespace wayland {

const struct wl_buffer_listener Buffer::listener_ = {
  Buffer::OnReleaseThunk,
};


Buffer::Buffer(struct wl_buffer* buffer) : Proxy(buffer) {
  wl_buffer_add_listener(id(), &listener_, this);
}

Buffer::~Buffer() {
  wl_buffer_destroy(id());
}

void Buffer::OnRelease(struct wl_buffer* buffer) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

// static
void Buffer::OnReleaseThunk(void* data, struct wl_buffer* buffer) {
  static_cast<Buffer*>(data)->OnRelease(buffer);
}

}  // namespace wayland
