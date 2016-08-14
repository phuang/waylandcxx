#ifndef __TOUCH_H_
#define __TOUCH_H_

#include <cstdint>

#include <wayland-client.h>

#include "proxy.h"

namespace wl {

class Touch : public Proxy<struct wl_touch, Touch> {
 public:
  Touch(struct wl_touch* touch);
  ~Touch();

 private:
  // Touch events:
  void OnDown(struct wl_touch* touch,
              uint32_t serial,
              uint32_t time,
              struct wl_surface* surface,
              int32_t id,
              wl_fixed_t surface_x,
              wl_fixed_t surface_y);
  void OnUp(struct wl_touch* touch,
            uint32_t serial,
            uint32_t time,
            int32_t id);
  void OnMotion(struct wl_touch* touch,
                uint32_t time,
                int32_t id,
                wl_fixed_t surface_x,
                wl_fixed_t surface_y);
  void OnFrame(struct wl_touch* touch);
  void OnCancel(struct wl_touch* touch);

  // static thunks:
  static void OnDownThunk(void* data,
                          struct wl_touch* touch,
                          uint32_t serial,
                          uint32_t time,
                          struct wl_surface* surface,
                          int32_t id,
                          wl_fixed_t surface_x,
                          wl_fixed_t surface_y);
  static void OnUpThunk(void* data,
                        struct wl_touch* touch,
                        uint32_t serial,
                        uint32_t time,
                        int32_t id);
  static void OnMotionThunk(void *data,
                            struct wl_touch* touch,
                            uint32_t time,
                            int32_t id,
                            wl_fixed_t surface_x,
                            wl_fixed_t surface_y);
  static void OnFrameThunk(void* data, struct wl_touch* touch);
  static void OnCancelThunk(void* data, struct wl_touch* touch);

  static const struct wl_touch_listener listener_;
};

}  // namespace wl

#endif
