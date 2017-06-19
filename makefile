CC=g++
CCFLAGS=-std=c++11 -lcurses -lpthread
CCF=${CC} ${CCFLAGS}

test:test.o KThread.o
	${CCF} -o $@ $^

test.o:test.cpp
	${CCF} -c $<

KThread.o:KThread.cpp KThread.h
	${CCF} -c $<

run:test
	./test

clean:
	rm *.o test
