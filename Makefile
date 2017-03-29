CXX = g++
LD = g++
MAKE = make
CFLAGS = -g -Wall --std=c++11

LDFLAGS =
LIBS = `pkg-config --static --libs x11 xrandr xi xxf86vm glew glfw3`

tfd = tinyfiledialogs
bmpread = libbmpread
DEPS = $(tfd)/libtfd.a $(bmpread)/libbmpread.a

INCLUDE = -Iinclude -I$(tfd) -I$(bmpread)
BIN_DIR = bin
OBJ_DIR = obj

OUT_BIN = conwaylife

ifeq ($(OS),Windows_NT)
	LIBS := -lmingw32 -lglfw3 -lglew32 -lopengl32 -lole32
	OUT_BIN := $(OUT_BIN).exe
	LDFLAGS += -mwindows
	MAKE := mingw32-make
endif

$(shell mkdir -p $(BIN_DIR) >/dev/null)
$(shell mkdir -p $(OBJ_DIR) >/dev/null)

DEPFLAGS = -MT $@ -MMD -MP -MF $(OBJ_DIR)/$*.Td

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%,$(OBJ_DIR)/%.o,$(basename $(SOURCES))) $(RESLOAD)

all: $(DEPS) $(BIN_DIR)/$(OUT_BIN)

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(tfd) clean
	$(MAKE) -C $(bmpread) clean

$(tfd)/libtfd.a:
	$(MAKE) -C $(tfd)

$(bmpread)/libbmpread.a:
	$(MAKE) -C $(bmpread)

$(RESLOAD): $(RESPACK)
$(RESPACK):
	$(MAKE) -C $(RESPACK_DIR)

$(BIN_DIR)/$(OUT_BIN): $(OBJECTS)
	$(LD) -o $(BIN_DIR)/$(OUT_BIN) $(OBJECTS) $(LDFLAGS) $(DEPS) $(LIBS)

$(OBJ_DIR)/%.o : src/%.cpp
$(OBJ_DIR)/%.o : src/%.cpp $(OBJ_DIR)/%.d
	$(CXX) $(DEPFLAGS) $(CFLAGS) -c $(INCLUDE) -o $@ $<
	@mv -f $(OBJ_DIR)/$*.Td $(OBJ_DIR)/$*.d

$(OBJ_DIR)/%.d: ;
.PRECIOUS: $(OBJ_DIR)/%.d

-include $(patsubst src/%,$(OBJ_DIR)/%.d,$(basename $(SOURCES)))