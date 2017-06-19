CC=g++
CCFLAGS=-std=c++11 -lcurses -lpthread
CCF=${CC} ${CCFLAGS}
OBJ=playball

${OBJ}:${OBJ}.o libkwidget.a
	${CCF} -o $@ $< -lkwidget -L "."

${OBJ}.o:${OBJ}.cpp
	${CCF} -c $<

#-------------   begin kwidget   -------------

libkwidget.a:KThread.o KApplication.o KObject.o
	ar cr $@ $^

KThread.o:KThread.cpp KThread.h KObject.o
	${CCF} -c $<

KApplication.o:KApplication.cpp KApplication.h KObject.o
	${CCF} -c $<

KObject.o:KObject.cpp KObject.h
	${CCF} -c $<

run:${OBJ}
	./${OBJ}

clean:
	rm *.o ${OBJ} *.a
