#include "buffer.h"

namespace wl {

const struct wl_buffer_listener Buffer::listener_ = {
    Buffer::OnReleaseThunk,
};

Buffer::Buffer(struct wl_buffer* buffer, Delegate* delegate)
    : Proxy(buffer), delegate_(delegate) {
  wl_buffer_add_listener(id(), &listener_, this);
}

Buffer::~Buffer() { wl_buffer_destroy(id()); }

void Buffer::OnRelease(struct wl_buffer* buffer) {
  if (delegate_) delegate_->OnRelease();
}

// static
void Buffer::OnReleaseThunk(void* data, struct wl_buffer* buffer) {
  static_cast<Buffer*>(data)->OnRelease(buffer);
}

}  // namespace wl
