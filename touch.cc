#include "touch.h"

#include <stdio.h>

namespace wl {

const struct wl_touch_listener Touch::listener_ = {
    Touch::OnDownThunk,  Touch::OnUpThunk,     Touch::OnMotionThunk,
    Touch::OnFrameThunk, Touch::OnCancelThunk,
};

Touch::Touch(struct wl_touch* touch) : Proxy(touch) {
  wl_touch_add_listener(id(), &listener_, this);
}

Touch::~Touch() { wl_touch_release(id()); }

void Touch::OnDown(struct wl_touch* touch, uint32_t serial, uint32_t time,
                   struct wl_surface* surface, int32_t id, wl_fixed_t surface_x,
                   wl_fixed_t surface_y) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Touch::OnUp(struct wl_touch* touch, uint32_t serial, uint32_t time,
                 int32_t id) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Touch::OnMotion(struct wl_touch* touch, uint32_t time, int32_t id,
                     wl_fixed_t surface_x, wl_fixed_t surface_y) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Touch::OnFrame(struct wl_touch* touch) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Touch::OnCancel(struct wl_touch* touch) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

// static
void Touch::OnDownThunk(void* data, struct wl_touch* touch, uint32_t serial,
                        uint32_t time, struct wl_surface* surface, int32_t id,
                        wl_fixed_t surface_x, wl_fixed_t surface_y) {
  static_cast<Touch*>(data)->OnDown(touch, serial, time, surface, id, surface_x,
                                    surface_y);
}

// static
void Touch::OnUpThunk(void* data, struct wl_touch* touch, uint32_t serial,
                      uint32_t time, int32_t id) {
  static_cast<Touch*>(data)->OnUp(touch, serial, time, id);
}

// static
void Touch::OnMotionThunk(void* data, struct wl_touch* touch, uint32_t time,
                          int32_t id, wl_fixed_t surface_x,
                          wl_fixed_t surface_y) {
  static_cast<Touch*>(data)->OnMotion(touch, time, id, surface_x, surface_y);
}

// static
void Touch::OnFrameThunk(void* data, struct wl_touch* touch) {
  static_cast<Touch*>(data)->OnFrame(touch);
}

// static
void Touch::OnCancelThunk(void* data, struct wl_touch* touch) {
  static_cast<Touch*>(data)->OnCancel(touch);
}

}  // namespace wl
