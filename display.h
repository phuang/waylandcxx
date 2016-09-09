#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include <memory>
#include <vector>

#include <wayland-client.h>
#include <wayland-egl.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include "proxy.h"
#include "registry.h"

namespace wl {

class Compositor;
class Seat;
class Shell;
class Shm;
class Subcompositor;

class Display : public Proxy<struct wl_display, Display>,
                public Registry::Delegate {
 public:
  Display();
  ~Display();

  static Display* current();

  void InitEGL();
  void Run();
  void Sync();

  Registry* registry() { return registry_.get(); }
  Compositor* compositor() { return compositor_.get(); }
  Subcompositor* subcompositor() { return subcompositor_.get(); }
  Shell* shell() { return shell_.get(); }
  Shm* shm() { return shm_.get(); }
  EGLDisplay egl_display() { return egl_display_; }
  EGLConfig egl_config() { return egl_config_; }
  EGLContext egl_context() { return egl_context_; }

 private:
  // Registry::Delegate overrides:
  void OnGlobal(uint32_t id, const char* interface, uint32_t version) override;
  void OnGlobalRemove(uint32_t id) override;

  // Event handlers:
  void OnError(struct wl_display* display, void* object_id, uint32_t code,
               const char* message);
  void OnDeleteId(struct wl_display* display, uint32_t id);

  // Event handler thunks:
  static void OnErrorThunk(void* data, struct wl_display* display,
                           void* object_id, uint32_t code, const char* message);
  static void OnDeleteIdThunk(void* data, struct wl_display* display,
                              uint32_t id);

  uint32_t seat_version_ = 0;
  uint32_t serial_ = 0;
  std::unique_ptr<Registry> registry_;
  std::unique_ptr<Compositor> compositor_;
  std::unique_ptr<Shell> shell_;
  std::unique_ptr<Shm> shm_;
  std::unique_ptr<Subcompositor> subcompositor_;
  std::vector<std::unique_ptr<Seat>> seats_;

  // EGL
  EGLDisplay egl_display_ = EGL_NO_DISPLAY;
  EGLConfig egl_config_;
  EGLContext egl_context_;

  static const struct wl_display_listener listener_;
};

}  // namespace wl

#endif
