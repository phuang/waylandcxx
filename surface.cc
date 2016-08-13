#include "surface.h"

#include "display.h"

namespace wayland {

const struct wl_surface_listener Surface::surface_listener_ = {
  Surface::OnEntryThunk,
  Surface::OnLeaveThunk,
};

Surface::Surface(struct wl_surface* surface)
  : Proxy(surface) {
  wl_surface_add_listener(id(), &surface_listener_, this);
}

Surface::~Surface() {
}

void Surface::OnEntry(struct wl_surface* surface,
                      struct wl_output* output) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Surface::OnLeave(struct wl_surface* surface,
                      struct wl_output* output) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

// static
void Surface::OnEntryThunk(void* data,
                           struct wl_surface* surface,
                           struct wl_output* output) {
  static_cast<Surface*>(data)->OnEntry(surface, output);
}

// static
void Surface::OnLeaveThunk(void* data,
                           struct wl_surface* surface,
                           struct wl_output* output) {
  static_cast<Surface*>(data)->OnLeave(surface, output);
}

}  // namespace wayland
