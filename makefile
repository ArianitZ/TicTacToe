CC = g++

COMPILER_FLAGS = -g

LINKER_FLAGS = -lSDL2 -lSDL2_image

DEPS = tic_tac_toe.cpp window.cpp texture.cpp player.cpp game.cpp

OUTPUT = tic_tac_toe.o

tic_tac_toe: ${DEPS}
	${CC} ${COMPILER_FLAGS} ${DEPS} ${LINKER_FLAGS} -o ${OUTPUT}

clean:
	rm -f *.o