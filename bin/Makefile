#Makefile for actrac

WX_INCLUDE_PATH=`/usr/wx3.2.2.1/wx-dynamic-build/wx-config --cppflags`
WX_LIBS=`/usr/wx3.2.2.1/wx-dynamic-build/wx-config --libs`

default: main

main: main.o
	$(INFO compiling.....)
	g++ -g -o actrac $(WX_LIBS) main.o

main.o:
	$(INFO compiling main.o)
	g++ -g -c -o main.o $(WX_INCLUDE_PATH) -I../include ../src/main.cpp

clean:
	rm *.o actrac