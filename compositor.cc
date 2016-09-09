#include "compositor.h"

#include "surface.h"

namespace wl {

Compositor::Compositor(struct wl_compositor* compositor) : Proxy(compositor) {}

Compositor::~Compositor() {}

std::unique_ptr<Surface> Compositor::CreateSurface() {
  return std::unique_ptr<Surface>(
      new Surface(wl_compositor_create_surface(id())));
}

}  // namespace wl
