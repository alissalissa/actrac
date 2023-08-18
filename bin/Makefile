#Makefile for actrac

WX_INCLUDE_PATH=`/usr/wx3.2.2.1/wx-dynamic-build/wx-config --cppflags`
WX_LIBS=`/usr/wx3.2.2.1/wx-dynamic-build/wx-config --libs`

default: main

main: main.o mainframe.o acdate.o activity.o aediag.o addtag.o
	$(INFO compiling.....)
	g++ -g -o actrac $(WX_LIBS) main.o addtag.o aediag.o mainframe.o acdate.o activity.o idgen.o

main.o: mainframe.o
	$(INFO compiling main.cpp)
	g++ -g -c -o main.o $(WX_INCLUDE_PATH) -I../include ../src/main.cpp

mainframe.o: acdate.o aediag.o
	$(INFO compiling mainframe.cpp)
	g++ -g -c -o mainframe.o $(WX_INCLUDE_PATH) -I../include ../src/mainframe.cpp

acdate.o: activity.o
	$(INFO compiling acdate.cpp)
	g++ -g -c -o acdate.o $(WX_INCLUDE_PATH) -I../include ../src/acdate.cpp

activity.o: idgen.o
	$(INFO compiling activity.cpp)
	g++ -g -c -o activity.o -I../include ../src/activity.cpp

idgen.o:
	$(INFO compiling idgen.cpp)
	g++ -g -c -o idgen.o -I../include ../src/idgen.cpp

aediag.o: addtag.o
	$(INFO compiling aediag.cpp)
	g++ -g -c -o aediag.o $(WX_INCLUDE_PATH) -I../include ../src/aediag.cpp

addtag.o:
	$(INFO compiling addtag.cpp)
	g++ -g -c -o addtag.o $(WX_INCLUDE_PATH) -I../include ../src/addtag.cpp

clean:
	rm *.o actrac