#include <assert.h>
#include <fcntl.h>
#include <GLES2/gl2.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#include "buffer.h"
#include "compositor.h"
#include "display.h"
#include "egl_window.h"
#include "shell.h"
#include "shell_surface.h"
#include "shm.h"
#include "shm_pool.h"
#include "subcompositor.h"
#include "subsurface.h"
#include "surface.h"

void init();
void reshape(int w, int h);
int draw();

void draw(int r, int g, int b, int a) {
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT);
}

class Window {
 public:
  Window() {
    auto dpy = wl::Display::current();
    surface_ = dpy->compositor()->CreateSurface();
    shell_surface_ = dpy->shell()->GetShellSurface(surface_.get(), nullptr);
    shell_surface_->SetToplevel();
  }
  ~Window() {}

  wl::Surface* surface() { return surface_.get(); }

 private:
  std::unique_ptr<wl::Surface> surface_;
  std::unique_ptr<wl::ShellSurface> shell_surface_;
};

class SharedMemory {
 public:
  SharedMemory() {}
  ~SharedMemory() {
    if (!memory_)
      munmap(memory_, size_);
    if (fd_ >= 0)
      close(fd_);
  }

  int fd() { return fd_; }
  int32_t size() { return size_; }
  void* memory() { return memory_; }

  bool Create(int32_t size) {
    assert(fd_ == -1);
    const char* kShmName = "/waytest";
    fd_ = shm_open(kShmName, O_RDWR | O_CREAT, 0777);
    if (fd_ < 0) {
      perror("shm_create");
      return false;
    }
    shm_unlink(kShmName);
    if (ftruncate(fd_, size_ = size) < 0)
      return false;
    memory_ = mmap(nullptr, size_, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
    return !memory_;
  }

 private:
  int fd_ = -1;
  int32_t size_ = 0;
  void* memory_ = nullptr;
};

const int32_t kBufferSize = 200 * 200 * 4;

int
main(int argc, char** argv) {
  std::unique_ptr<wl::Display> display(new wl::Display());

  Window w;
#if 0
  wl::EGLWindow egl_window(w.surface(), 200, 200);
  egl_window.MakeCurrent();
  init();
  reshape(300, 300);
  draw();
  //draw(1, 0, 0, 1);
  egl_window.SwapBuffers();
#else
  SharedMemory shared_memory;
  shared_memory.Create(kBufferSize * 3);
  std::unique_ptr<wl::ShmPool> pool =
      display->shm()->CreatePool(shared_memory.fd(), shared_memory.size());

  auto buffer_0 = pool->CreateBuffer(nullptr, 0, 200, 200, 200 * 4, 0);
  int32_t* pixels = static_cast<int32_t*>(shared_memory.memory());
  int r = 0, g = 0, b = 0;
  for (int x = 0; x < 200; ++x) {
    for (int y = 0; y < 200; ++y) {
      r = x;
      g = y;
      b = (x + (255 - y)) / 2;
      *pixels = 0xff000000 | r | (g << 8)| (b << 16);
      pixels++;
    }
  }
  w.surface()->Attach(buffer_0.get(), 0, 0);
#endif
#if 0
  auto surface2 = display->compositor()->CreateSurface();

  auto subsurface = display->subcompositor()->GetSubsurface(surface2.get(),
                                                            w.surface());
  subsurface->SetPosition(100, 100);
  wl::EGLWindow egl_window2(surface2.get(), 50, 50);
  egl_window2.MakeCurrent();
  draw(0, 0, 1, 1);
  egl_window2.SwapBuffers();
#endif

  w.surface()->Commit();
  display->Run();
}
