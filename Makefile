CC = clang

MAKEFLAGS := --jobs=$(shell nproc)

SRC := src
OBJ := obj
BIN := gtkui

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
HEADERS := $(wildcard $(SRC)/*.hpp)

CFLAGS  := -std=c++17
LDFLAGS := -lstdc++ -lstdc++fs

debug: CFLAGS += -O0
debug: $(BIN)

release: CFLAGS += -O2
release: $(BIN)

$(BIN): $(OBJECTS) $(HEADERS)
	$(CC) -o $(BIN) $(OBJECTS) $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ):
	mkdir -p $@

clean_debug: clean
	+@$(MAKE) --no-print-directory debug

clean_release: clean
	+@$(MAKE) --no-print-directory release

clean:
	-rm -r $(OBJ)