CC = clang++ 
LAND_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors 
INCLUDE_PATH = -I"./libs"
SRC_FILES = src/*.cpp \
						./libs/imgui/*.cpp 

LINKER_FLAGS = `pkg-config --libs --cflags sdl3 sdl3-image`
OBJ_NAME = StarterApp 

build:
	$(CC) $(COMPILER_FLAGS) $(LAND_STD) $(INCLUDE_PATH) $(SRC_FILES) -o $(OBJ_NAME) $(LINKER_FLAGS)

run:
	./$(OBJ_NAME)
