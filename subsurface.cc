#include "subsurface.h"

namespace wl {

Subsurface::Subsurface(struct wl_subsurface* subsurface) : Proxy(subsurface) {
}

Subsurface::~Subsurface() {
  wl_subsurface_destroy(id());
}

void Subsurface::SetPosition(int32_t x, int32_t y) {
  wl_subsurface_set_position(id(), x, y);
}

void Subsurface::PlaceAbove(Surface* sibling) {
  wl_subsurface_place_above(id(), sibling->id());
}

void Subsurface::PlaceBelow(Surface* sibling) {
  wl_subsurface_place_below(id(), sibling->id());
}

void Subsurface::SetSync() {
  wl_subsurface_set_sync(id());
}

void Subsurface::SetDesync() {
  wl_subsurface_set_desync(id());
}

}  // namespace wl
