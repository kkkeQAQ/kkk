CC=g++
CCFLAGS=-std=c++11 -lcurses -lpthread
CCF=${CC} ${CCFLAGS}
OBJ=playball

${OBJ}:${OBJ}.o KThread.o
	${CCF} -o $@ $^

${OBJ}.o:${OBJ}.cpp
	${CCF} -c $<

KThread.o:KThread.cpp KThread.h
	${CCF} -c $<

run:${OBJ}
	./${OBJ}

clean:
	rm *.o ${OBJ}
