#ifndef __SUBSURFACE_H_
#define __SUBSURFACE_H_

#include <wayland-client.h>

#include "proxy.h"
#include "surface.h"

namespace wl {

class Surface;

class Subsurface : public Proxy<struct wl_subsurface, Subsurface> {
 public:
  explicit Subsurface(struct wl_subsurface* subsurface);
  ~Subsurface();

  void SetPosition(int32_t x, int32_t y);
  void PlaceAbove(Surface* sibling);
  void PlaceBelow(Surface* sibling);
  void SetSync();
  void SetDesync();
};

}  // namespace wl


#endif
