#include "keyboard.h"

#include <stdio.h>

namespace wl {

const struct wl_keyboard_listener Keyboard::listener_ = {
    Keyboard::OnKeymapThunk,    Keyboard::OnEnterThunk,
    Keyboard::OnLeaveThunk,     Keyboard::OnKeyThunk,
    Keyboard::OnModifiersThunk, Keyboard::OnRepeatInfoThunk,
};

Keyboard::Keyboard(struct wl_keyboard* keyboard) : Proxy(keyboard) {
  wl_keyboard_add_listener(id(), &listener_, this);
}

Keyboard::~Keyboard() { wl_keyboard_release(id()); }

void Keyboard::OnKeymap(struct wl_keyboard* keyboard, uint32_t format,
                        int32_t fd, uint32_t size) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Keyboard::OnEnter(struct wl_keyboard* keyboard, uint32_t serial,
                       struct wl_surface* surface, struct wl_array* keys) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Keyboard::OnLeave(struct wl_keyboard* keyboard, uint32_t serial,
                       struct wl_surface* surface) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Keyboard::OnKey(struct wl_keyboard* keyboard, uint32_t serial,
                     uint32_t time, uint32_t key, uint32_t state) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Keyboard::OnModifiers(struct wl_keyboard* keyboard, uint32_t serial,
                           uint32_t mods_depressed, uint32_t mods_latched,
                           uint32_t mods_locked, uint32_t group) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

void Keyboard::OnRepeatInfo(struct wl_keyboard* wl_keyboard, int32_t rate,
                            int32_t delay) {
  fprintf(stderr, "%s this=%p\n", __PRETTY_FUNCTION__, this);
}

// static
void Keyboard::OnKeymapThunk(void* data, struct wl_keyboard* keyboard,
                             uint32_t format, int32_t fd, uint32_t size) {
  static_cast<Keyboard*>(data)->OnKeymap(keyboard, format, fd, size);
}

// static
void Keyboard::OnEnterThunk(void* data, struct wl_keyboard* keyboard,
                            uint32_t serial, struct wl_surface* surface,
                            struct wl_array* keys) {
  static_cast<Keyboard*>(data)->OnEnter(keyboard, serial, surface, keys);
}

// static
void Keyboard::OnLeaveThunk(void* data, struct wl_keyboard* keyboard,
                            uint32_t serial, struct wl_surface* surface) {
  static_cast<Keyboard*>(data)->OnLeave(keyboard, serial, surface);
}

// static
void Keyboard::OnKeyThunk(void* data, struct wl_keyboard* keyboard,
                          uint32_t serial, uint32_t time, uint32_t key,
                          uint32_t state) {
  static_cast<Keyboard*>(data)->OnKey(keyboard, serial, time, key, state);
}

// static
void Keyboard::OnModifiersThunk(void* data, struct wl_keyboard* keyboard,
                                uint32_t serial, uint32_t mods_depressed,
                                uint32_t mods_latched, uint32_t mods_locked,
                                uint32_t group) {
  static_cast<Keyboard*>(data)->OnModifiers(keyboard, serial, mods_depressed,
                                            mods_latched, mods_locked, group);
}

// static
void Keyboard::OnRepeatInfoThunk(void* data, struct wl_keyboard* keyboard,
                                 int32_t rate, int32_t delay) {
  static_cast<Keyboard*>(data)->OnRepeatInfo(keyboard, rate, delay);
}

}  // namespace wl
