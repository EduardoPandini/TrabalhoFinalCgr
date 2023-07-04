# Compiler and compiler flags
CC = g++
CFLAGS = -std=c++11 -Wall -Wextra

# SFML libraries

SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Directories
SRC_DIR = .
OBJ_DIR = obj

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))


# Main target
jogo2d: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(SFML_LIBS) -lGL

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean command
clean:
	rm -f jogo2d
	rm -rf $(OBJ_DIR)

.PHONY: clean
