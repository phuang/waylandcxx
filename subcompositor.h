#ifndef __SUBCOMPOSITOR_H_
#define __SUBCOMPOSITOR_H_

#include <wayland-client.h>
#include <memory>

#include "proxy.h"

namespace wl {

class Subsurface;
class Surface;

class Subcompositor : public Proxy<struct wl_subcompositor, Subcompositor> {
 public:
  explicit Subcompositor(struct wl_subcompositor* subcompositor);
  ~Subcompositor();

  std::unique_ptr<Subsurface> GetSubsurface(Surface* surface, Surface* parent);
};

}  // namespace wl
#endif
