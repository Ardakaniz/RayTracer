SRC_DIR = Sources
OBJ_DIR = obj
SRC_FILES = $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

CC = g++
FLAGS = -Wall -Wpedantic -I$(SRC_DIR)
OUT = raytracer
LDFLAGS = -lsfml-graphics

raytracer: $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(FLAGS) -std=c++20 -c -o $@ $<

r: $(OUT)
	./$(OUT)
	open image.png

clean:
	@find $(OBJ_DIR) -type f -delete
	@rm $(OUT)