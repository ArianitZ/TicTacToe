CC = g++

COMPILER_FLAGS = -g

LINKER_FLAGS = -lSDL2

DEPS = tic_tac_toe.cpp window.cpp

OUTPUT = tic_tac_toe.o

tic_tac_toe: ${DEPS}
	${CC} ${COMPILER_FLAGS} ${DEPS} ${LINKER_FLAGS} -o ${OUTPUT}

clean:
	rm -f tic_tac_toe.o