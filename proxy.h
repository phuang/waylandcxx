#ifndef __PROXY_H_
#define __PROXY_H_

#include <wayland-client.h>

namespace wl {

template<typename T, typename C>
class Proxy {
 public:
  explicit Proxy(T* id) : id_(id) {
    if (id_)
      wl_proxy_set_user_data(reinterpret_cast<struct wl_proxy*>(id_), this);
  }

  ~Proxy() {}
  T* id() { return id_; }

  static C* From(T* id) {
    return reinterpret_cast<C*>(wl_proxy_get_user_data(id));
  }

 private:
  T* const id_;
};

}  // namespace wl

#endif
