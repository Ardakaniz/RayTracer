SRC_DIR = Sources
OBJ_DIR = obj
SRC_FILES = $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

CC = g++
FLAGS = -Wall -Wpedantic -ISources
OUT = raytracer
LDFLAGS = -lsfml-graphics

raytracer: $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(FLAGS) -std=c++17 -c -o $@ $<

clean:
	@find obj -type f -delete
	@rm raytracer