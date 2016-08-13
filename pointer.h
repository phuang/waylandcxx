#ifndef __POINTER_H_
#define __POINTER_H_

#include <cstdint>

#include <wayland-client.h>

#include "proxy.h"

namespace wayland {

class Pointer : public Proxy<struct wl_pointer, Pointer> {
 public:
  Pointer(struct wl_pointer* pointer);
  ~Pointer();

 private:
  // Event handlers:
  void OnEnter(struct wl_pointer* pointer,
               uint32_t serial,
               struct wl_surface* surface,
               wl_fixed_t surface_x,
               wl_fixed_t surface_y);
  void OnLeave(struct wl_pointer* pointer,
               uint32_t serial,
               struct wl_surface* surface);
  void OnMotion(struct wl_pointer* pointer,
                uint32_t time,
                wl_fixed_t surface_x,
                wl_fixed_t surface_y);
  void OnButton(struct wl_pointer* pointer,
                uint32_t serial,
                uint32_t time,
                uint32_t button,
                uint32_t state);
  void OnAxis(struct wl_pointer* pointer,
              uint32_t time,
              uint32_t axis,
              wl_fixed_t value);
  void OnFrame(struct wl_pointer* pointer);
  void OnAxisSource(struct wl_pointer* pointer,
                    uint32_t axis_source);
  void OnAxisStop(struct wl_pointer* pointer,
                  uint32_t time,
                  uint32_t axis);

  // Event handler thunks:
  static void OnEnterThunk(void* data,
                           struct wl_pointer* pointer,
                           uint32_t serial,
                           struct wl_surface* surface,
                           wl_fixed_t surface_x,
                           wl_fixed_t surface_y);
  static void OnLeaveThunk(void* data,
                           struct wl_pointer* pointer,
                           uint32_t serial,
                           struct wl_surface* surface);
  static void OnMotionThunk(void* data,
                            struct wl_pointer* pointer,
                            uint32_t time,
                            wl_fixed_t surface_x,
                            wl_fixed_t surface_y);
  static void OnButtonThunk(void* data,
                            struct wl_pointer* pointer,
                            uint32_t serial,
                            uint32_t time,
                            uint32_t button,
                            uint32_t state);
  static void OnAxisThunk(void* data,
                          struct wl_pointer* pointer,
                          uint32_t time,
                          uint32_t axis,
                          wl_fixed_t value);
  static void OnFrameThunk(void* data, struct wl_pointer* pointer);
  static void OnAxisSourceThunk(void* data,
                                struct wl_pointer* pointer,
                                uint32_t axis_source);
  static void OnAxisStopThunk(void* data,
                              struct wl_pointer* pointer,
                              uint32_t time, uint32_t axis);

  static const struct wl_pointer_listener listener_;
};

}  // namespace wayland

#endif
