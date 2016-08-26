#include "pointer.h"

#include <stdio.h>

namespace wl {

const struct wl_pointer_listener Pointer::listener_ = {
  Pointer::OnEnterThunk,
  Pointer::OnLeaveThunk,
  Pointer::OnMotionThunk,
  Pointer::OnButtonThunk,
  Pointer::OnAxisThunk,
#if 0
  Pointer::OnFrameThunk,
  Pointer::OnAxisSourceThunk,
  Pointer::OnAxisStopThunk,
#endif
};

Pointer::Pointer(struct wl_pointer* pointer)
  : Proxy(pointer) {
    wl_pointer_add_listener(id(), &listener_, this);
}

Pointer::~Pointer() {
  wl_pointer_release(id());
}

void Pointer::OnEnter(struct wl_pointer* pointer,
                      uint32_t serial,
                      struct wl_surface* surface,
                      wl_fixed_t surface_x,
                      wl_fixed_t surface_y) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Pointer::OnLeave(struct wl_pointer* pointer,
                      uint32_t serial,
                      struct wl_surface* surface) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Pointer::OnMotion(struct wl_pointer* pointer,
                       uint32_t time,
                       wl_fixed_t surface_x,
                       wl_fixed_t surface_y) {
  float x = wl_fixed_to_double(surface_x);
  float y = wl_fixed_to_double(surface_y);
  fprintf(stderr, "%s this=%p x=%f y=%f time=%u\n", __PRETTY_FUNCTION__, this, x, y, time);
}

void Pointer::OnButton(struct wl_pointer* pointer,
                       uint32_t serial,
                       uint32_t time,
                       uint32_t button,
                       uint32_t state) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Pointer::OnAxis(struct wl_pointer* pointer,
                     uint32_t time,
                     uint32_t axis,
                     wl_fixed_t value) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Pointer::OnFrame(struct wl_pointer* pointer) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Pointer::OnAxisSource(struct wl_pointer* pointer, uint32_t axis_source) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Pointer::OnAxisStop(struct wl_pointer* pointer, uint32_t time,
                         uint32_t axis) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

// static
void Pointer::OnEnterThunk(void* data,
                           struct wl_pointer* pointer,
                           uint32_t serial,
                           struct wl_surface* surface,
                           wl_fixed_t surface_x,
                           wl_fixed_t surface_y) {
  static_cast<Pointer*>(data)->OnEnter(
      pointer, serial, surface, surface_x, surface_y);
}

// static
void Pointer::OnLeaveThunk(void* data,
                           struct wl_pointer* pointer,
                           uint32_t serial,
                           struct wl_surface* surface) {
  static_cast<Pointer*>(data)->OnLeave(pointer, serial, surface);
}

// static
void Pointer::OnMotionThunk(void* data,
                            struct wl_pointer* pointer,
                            uint32_t time,
                            wl_fixed_t surface_x,
                            wl_fixed_t surface_y) {
  static_cast<Pointer*>(data)->OnMotion(pointer, time, surface_x, surface_y);
}

// static
void Pointer::OnButtonThunk(void* data,
                            struct wl_pointer* pointer,
                            uint32_t serial,
                            uint32_t time,
                            uint32_t button,
                            uint32_t state) {
  static_cast<Pointer*>(data)->OnButton(pointer, serial, time, button, state);
}

// static
void Pointer::OnAxisThunk(void* data,
                          struct wl_pointer* pointer,
                          uint32_t time,
                          uint32_t axis,
                          wl_fixed_t value) {
  static_cast<Pointer*>(data)->OnAxis(pointer, time, axis, value);
}

// static
void Pointer::OnFrameThunk(void* data, struct wl_pointer* pointer) {
  static_cast<Pointer*>(data)->OnFrame(pointer);
}

// static
void Pointer::OnAxisSourceThunk(void* data,
                                struct wl_pointer* pointer,
                                uint32_t axis_source) {
  static_cast<Pointer*>(data)->OnAxisSource(pointer, axis_source);
}

// static
void Pointer::OnAxisStopThunk(void* data,
                              struct wl_pointer* pointer,
                              uint32_t time,
                              uint32_t axis) {
  static_cast<Pointer*>(data)->OnAxisStop(pointer, time, axis);
}

}   // namespace wl
