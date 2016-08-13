#ifndef __SEAT_H_
#define __SEAT_H_

#include <memory>
#include <string>

#include <wayland-client.h>

#include "proxy.h"

namespace wayland {

class Keyboard;
class Pointer;
class Touch;

class Seat : public Proxy<struct wl_seat, Seat> {
 public:
  Seat(struct wl_seat* seat);
  ~Seat();

 private:
  // Event handlers:
  void OnCapabilities(struct wl_seat* seat, uint32_t caps);
  void OnName(struct wl_seat* seat, const char* name);
 
  // Event handler thhunks:
  static void OnCapabilitiesThunk(void* data,
                                  struct wl_seat* seat,
                                  uint32_t caps);
  static void OnNameThunk(void* data,
                          struct wl_seat* seat,
                          const char* name);

  // unique identifiers for this seat.
  std::string name_;

  std::unique_ptr<Keyboard> keyboard_;
  std::unique_ptr<Pointer> pointer_;
  std::unique_ptr<Touch> touch_;

  static const struct wl_seat_listener listener_;
};

}  // namespace wayland

#endif
