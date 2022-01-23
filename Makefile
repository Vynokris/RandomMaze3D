PROGRAM = intro_gl
OBJS    = src/main.o src/gl.o src/draw.o src/maths.o src/bmpLoader.o src/mazeGen.o src/camera.o

CXX      = g++
CXXFLAGS = -O0 -g -Wall -Wno-unused-variable
CPPFLAGS = -Iexternals/include -MMD

ifeq ($(OS), Windows_NT)
PROGRAM   = intro_gl.exe
CXX       = clang++
CXXFLAGS += -std=c++17 -D_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH=1 -nostdlib
LDFLAGS   = -Lexternals/lib-vc2019
LDLIBS    = -lglfw3 -lglu32 -lgdi32 -luser32 -lshell32# -lglfw3dll -lopengl32

else 
TARGET ?= $(shell $(CXX) -dumpmachine)
LDFLAGS = -Lexternals/libs-$(TARGET)

ifeq ($(TARGET), x86_64-pc-cygwin)
LDLIBS = -lglfw3 -lgdi32 -lglu32

else ifeq ($(TARGET), x86_64-pc-linux-gnu)
LDLIBS = -lglfw3 -ldl -lX11 -lssl -lpthread -lGLU

else ifeq ($(TARGET), x86_64-linux-gnu)
LDLIBS = -lglfw3 -ldl -lX11 -lssl -lpthread -lGLU

endif
endif

DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: $(PROGRAM)

-include $(DEPS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f $(PROGRAM) $(OBJS) $(DEPS) && clear
