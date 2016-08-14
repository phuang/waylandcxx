#ifndef __SURFACE_H_
#define __SURFACE_H_

#include <wayland-client.h>
#include <wayland-egl.h>

#include "proxy.h"

namespace wayland {

class Buffer;

class Surface : public Proxy<struct wl_surface, Surface> {
 public:
  explicit Surface(struct wl_surface* surface);
  ~Surface();

  void Attach(Buffer* buffer, int32_t x, int32_t y);
  void Damage(int32_t x, int32_t y, int32_t width, int32_t height);
  struct wl_callback* Frame();
  void SetOpaqueRegion(struct wl_region* region);
  void SetInputRegion(struct wl_region* region);
  void Commit();
  void SetBufferTransform(int32_t transform);
  void SetBufferScale(int32_t scale);
#if defined(WL_SURFACE_DAMAGE_BUFFER)
  void DamageBuffer(int32_t x, int32_t y, int32_t width, int32_t height);
#endif
  
 private:
  // Event handlers:
  void OnEntry(struct wl_surface* surface,
               struct wl_output* output);
  void OnLeave(struct wl_surface* surface,
               struct wl_output* output);

  // Event handler thunks:
  static void OnEntryThunk(void* data,
                           struct wl_surface* surface,
                           struct wl_output* output);
  static void OnLeaveThunk(void* data,
                           struct wl_surface* surface,
                           struct wl_output* output);

  struct wl_egl_window* egl_window_;

  const static wl_surface_listener surface_listener_;
};

}

#endif
