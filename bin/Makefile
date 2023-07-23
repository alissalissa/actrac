#Makefile for actrac

WX_INCLUDE_PATH=`/usr/wx3.2.2.1/wx-dynamic-build/wx-config --cppflags`
WX_LIBS=`/usr/wx3.2.2.1/wx-dynamic-build/wx-config --libs`

default: main

main: main.o mainframe.o
	$(INFO compiling.....)
	g++ -g -o actrac $(WX_LIBS) main.o mainframe.o

main.o:
	$(INFO compiling main.cpp)
	g++ -g -c -o main.o $(WX_INCLUDE_PATH) -I../include ../src/main.cpp

mainframe.o:
	$(INFO compiling mainframe.cpp)
	g++ -g -c -o mainframe.o $(WX_INCLUDE_PATH) -I../include ../src/mainframe.cpp

clean:
	rm *.o actrac