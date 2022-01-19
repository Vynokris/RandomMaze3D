TARGET?=$(shell $(CXX) -dumpmachine)

BIN=intro_gl
CXXFLAGS=-Wall -Wno-unused-variable -O0 -g
CFLAGS=$(CXXFLAGS)
CPPFLAGS=-Iexternals/include -MMD
LDFLAGS=-Lexternals/libs-$(TARGET)

ifeq ($(TARGET), x86_64-pc-cygwin)
LDLIBS=-lglfw3 -lgdi32 -lglu32
else ifeq ($(TARGET), x86_64-pc-linux-gnu)
LDLIBS=-lglfw3 -ldl -lX11 -lssl -lpthread -lGLU
else ifeq ($(TARGET), x86_64-linux-gnu)
LDLIBS=-lglfw3 -ldl -lX11 -lssl -lpthread -lGLU
endif

OBJS=src/main.o src/gl.o src/draw.o src/glUtility.o
DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: $(BIN)

-include $(DEPS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f $(BIN) $(OBJS) $(DEPS)
