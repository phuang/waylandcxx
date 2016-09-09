#ifndef __KEYBOARD_H_
#define __KEYBOARD_H_

#include <cstdint>

#include <wayland-client.h>

#include "proxy.h"

namespace wl {

class Keyboard : public Proxy<struct wl_keyboard, Keyboard> {
 public:
  Keyboard(struct wl_keyboard* keyboard);
  ~Keyboard();

 private:
  // Event handlers:
  void OnKeymap(struct wl_keyboard* keyboard, uint32_t format, int32_t fd,
                uint32_t size);
  void OnEnter(struct wl_keyboard* keyboard, uint32_t serial,
               struct wl_surface* surface, struct wl_array* keys);
  void OnLeave(struct wl_keyboard* keyboard, uint32_t serial,
               struct wl_surface* surface);
  void OnKey(struct wl_keyboard* keyboard, uint32_t serial, uint32_t time,
             uint32_t key, uint32_t state);
  void OnModifiers(struct wl_keyboard* keyboard, uint32_t serial,
                   uint32_t mods_depressed, uint32_t mods_latched,
                   uint32_t mods_locked, uint32_t group);
  void OnRepeatInfo(struct wl_keyboard* wl_keyboard, int32_t rate,
                    int32_t delay);

  // Event handler thunks:
  static void OnKeymapThunk(void* data, struct wl_keyboard* keyboard,
                            uint32_t format, int32_t fd, uint32_t size);
  static void OnEnterThunk(void* data, struct wl_keyboard* keyboard,
                           uint32_t serial, struct wl_surface* surface,
                           struct wl_array* keys);
  static void OnLeaveThunk(void* data, struct wl_keyboard* keyboard,
                           uint32_t serial, struct wl_surface* surface);
  static void OnKeyThunk(void* data, struct wl_keyboard* keyboard,
                         uint32_t serial, uint32_t time, uint32_t key,
                         uint32_t state);
  static void OnModifiersThunk(void* data, struct wl_keyboard* keyboard,
                               uint32_t serial, uint32_t mods_depressed,
                               uint32_t mods_latched, uint32_t mods_locked,
                               uint32_t group);
  static void OnRepeatInfoThunk(void* data, struct wl_keyboard* keyboard,
                                int32_t rate, int32_t delay);

  static const struct wl_keyboard_listener listener_;
};

}  // namespace wl

#endif
