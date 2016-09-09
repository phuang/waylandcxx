#include "seat.h"

#include <stdio.h>

#include "keyboard.h"
#include "pointer.h"
#include "touch.h"

namespace wl {

const struct wl_seat_listener Seat::listener_ = {
    Seat::OnCapabilitiesThunk, Seat::OnNameThunk,
};

Seat::Seat(struct wl_seat* seat) : Proxy(seat) {
  wl_seat_add_listener(id(), &listener_, this);
}

Seat::~Seat() {
#if defined(WL_SEAT_RELEASE)
  wl_seat_release(id());
#endif
}

void Seat::OnCapabilities(struct wl_seat* seat, uint32_t caps) {
  if ((caps && WL_SEAT_CAPABILITY_KEYBOARD) && !keyboard_) {
    keyboard_.reset(new Keyboard(wl_seat_get_keyboard(id())));
  }
  if ((caps & WL_SEAT_CAPABILITY_POINTER) && !pointer_) {
    pointer_.reset(new Pointer(wl_seat_get_pointer(id())));
  }
  if ((caps & WL_SEAT_CAPABILITY_TOUCH) && !touch_) {
    touch_.reset(new Touch(wl_seat_get_touch(id())));
  }
}

void Seat::OnName(struct wl_seat* seat, const char* name) { name_ = name; }

// static
void Seat::OnCapabilitiesThunk(void* data, struct wl_seat* seat,
                               uint32_t caps) {
  static_cast<Seat*>(data)->OnCapabilities(seat, caps);
}

// static
void Seat::OnNameThunk(void* data, struct wl_seat* seat, const char* name) {
  static_cast<Seat*>(data)->OnName(seat, name);
}

}  // namespace wl
