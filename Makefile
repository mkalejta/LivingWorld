CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -IC:/libs/SDL2-2.0.22/include
LDFLAGS = -LC:/libs/SDL2-2.0.22/lib/x64 -lSDL2main -lSDL2

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Wyklucz LivingWorld.cpp z kompilacji
SOURCES := $(filter-out $(SRC_DIR)/LivingWorld.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# SDLWindow.cpp jest w głównym katalogu
MAIN_SRC = SDLWindow.cpp
MAIN_OBJ = $(OBJ_DIR)/SDLWindow.o

EXECUTABLE = $(BIN_DIR)/SDLWindow

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(MAIN_OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Kompilacja plików z katalogu src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Kompilacja SDLWindow.cpp z głównego katalogu
$(MAIN_OBJ): $(MAIN_SRC) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) *.o

.PHONY: all clean
