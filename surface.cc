#include "surface.h"

#include "buffer.h"

namespace wl {

const struct wl_surface_listener Surface::surface_listener_ = {
    Surface::OnEntryThunk, Surface::OnLeaveThunk,
};

Surface::Surface(struct wl_surface* surface) : Proxy(surface) {
  wl_surface_add_listener(id(), &surface_listener_, this);
}

Surface::~Surface() {}

void Surface::Attach(Buffer* buffer, int32_t x, int32_t y) {
  wl_surface_attach(id(), buffer->id(), x, y);
}

void Surface::Damage(int32_t x, int32_t y, int32_t width, int32_t height) {
  wl_surface_damage(id(), x, y, width, height);
}

struct wl_callback* Surface::Frame() {
  return wl_surface_frame(id());
}

void Surface::SetOpaqueRegion(struct wl_region* region) {
  wl_surface_set_opaque_region(id(), region);
}

void Surface::SetInputRegion(struct wl_region* region) {
  wl_surface_set_input_region(id(), region);
}

void Surface::Commit() { wl_surface_commit(id()); }

void Surface::SetBufferTransform(int32_t transform) {
  wl_surface_set_buffer_transform(id(), transform);
}

void Surface::SetBufferScale(int32_t scale) {
  wl_surface_set_buffer_scale(id(), scale);
}

#if defined(WL_SURFACE_DAMAGE_BUFFER)
void Surface::DamageBuffer(int32_t x, int32_t y, int32_t width,
                           int32_t height) {
  wl_surface_damage_buffer(id(), x, y, width, height);
}
#endif

void Surface::OnEntry(struct wl_surface* surface, struct wl_output* output) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Surface::OnLeave(struct wl_surface* surface, struct wl_output* output) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

// static
void Surface::OnEntryThunk(void* data, struct wl_surface* surface,
                           struct wl_output* output) {
  static_cast<Surface*>(data)->OnEntry(surface, output);
}

// static
void Surface::OnLeaveThunk(void* data, struct wl_surface* surface,
                           struct wl_output* output) {
  static_cast<Surface*>(data)->OnLeave(surface, output);
}

}  // namespace wl
