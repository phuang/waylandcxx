CC = clang++
CXX = clang++
CXXFLAGS = -std=c++11 -MMD -g
LDFLAGS = -lwayland-client -lwayland-egl -lEGL -lGLESv2

SOURCES = \
	callback.cc \
	compositor.cc \
	display.cc \
	keyboard.cc \
	main.cc \
	pointer.cc \
	registry.cc \
	seat.cc \
	shell.cc \
	shell_surface.cc \
	subcompositor.cc \
	subsurface.cc \
	surface.cc \
	touch.cc \
	$(NULL)

HEADERS = \
	callback.h \
	compositor.h \
	display.h \
	keyboard.h \
	main.h \
	pointer.h \
	registry.h \
	seat.h \
	shell.h \
	shell_surface.h \
	subcompositor.h \
	subsurface.h \
	surface.h \
	touch.h \
	$(NULL)

OBJECTS = $(SOURCES:.cc=.o)
DEPS = $(SOURCES:.cc=.d)

test: waytest
	./waytest

waytest: $(OBJECTS)
	$(CC) $(LDFLAGS) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(OBJECTS) $(DEPS) *~ waytest

-include $(DEPS)
