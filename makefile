OUTPUT = invaders.exe

c_files= src/Window.cpp \
src/game.cpp \
src/Texture.cpp \
src/Entity.cpp \
src/Enemy.cpp \
src/Player.cpp

h_files=$(addprefix inc/,$(notdir $(c_files:.cpp=.hpp)))

library_path=-LC:\mingw_dev_lib\lib

include_path=-IC:\mingw_dev_lib\include\SDL2

linker_flags=-lSDL2 -lSDL2main -lmingw32 -lSDL2_ttf -lSDL2_image

compiler_flags=-g -Wall -Wextra

all: $(c_files) $(h_files)
	g++ $(c_files) $(include_path) $(library_path) $(compiler_flags) $(linker_flags) -o $(OUTPUT) 

clean:
	rm -rf $(OUTPUT)

eval:
	gcc src/eval.c -mwindows -g -o eval.exe

gui:
	g++ $(c_files) src/gui.cpp src/Window.cpp $(compiler_flags) $(linker_flags) $(include_path) $(library_path) -o gui.exe 