#Makefile for actrac

WX_INCLUDE_PATH=`/usr/wx3.2.4/wx-dynamic-build/wx-config --cppflags`
WX_LIBS=`/usr/wx3.2.4/wx-dynamic-build/wx-config --libs`

default: main

main: main.o mainframe.o rpanel.o acdate.o activity.o aediag.o addtag.o idgen.o dvmodel.o serialize.o acreport.o
	$(info linking.....)
	clang++ -g -o actrac $(WX_LIBS) main.o addtag.o aediag.o mainframe.o dvmodel.o acdate.o activity.o idgen.o serialize.o acreport.o rpanel.o

main.o: mainframe.o
	$(info compiling main.cpp)
	clang++ -g -c -o main.o $(WX_INCLUDE_PATH) -I../include ../src/main.cpp

mainframe.o: acdate.o aediag.o dvmodel.o serialize.o acreport.o
	$(info compiling mainframe.cpp)
	clang++ -g -c -o mainframe.o $(WX_INCLUDE_PATH) -I../include ../src/mainframe.cpp

acdate.o: activity.o
	$(info compiling acdate.cpp)
	clang++ -g -c -o acdate.o $(WX_INCLUDE_PATH) -I../include ../src/acdate.cpp

activity.o: idgen.o
	$(info compiling activity.cpp)
	clang++ -g -c -o activity.o -I../include ../src/activity.cpp

idgen.o:
	$(info compiling idgen.cpp)
	clang++ -g -c -o idgen.o -I../include ../src/idgen.cpp

aediag.o: addtag.o
	$(info compiling aediag.cpp)
	clang++ -g -c -o aediag.o $(WX_INCLUDE_PATH) -I../include ../src/aediag.cpp

addtag.o:
	$(info compiling addtag.cpp)
	clang++ -g -c -o addtag.o $(WX_INCLUDE_PATH) -I../include ../src/addtag.cpp

dvmodel.o:
	$(info compiling dvmodel.cpp)
	clang++ -g -c -o dvmodel.o $(WX_INCLUDE_PATH) -I../include ../src/dvmodel.cpp

serialize.o: activity.o acdate.o
	$(info compiling serialize.cpp)
	clang++ -g -c -o serialize.o $(WX_INCLUDE_PATH) -I../include ../src/serialize.cpp

#acutil.o:
#	$(info compiling acutil.cpp)
#	clang++ -g -c -o acutil.o $(WX_INCLUDE_PATH) -I../include ../src/acutil.cpp

acreport.o: activity.o acdate.o
	$(info compiling acreport.cpp)
	clang++ -g -c -o acreport.o $(WX_INCLUDE_PATH) -I../include ../src/acreport.cpp

rpanel.o: acreport.o
	$(info compiling rpanel.cpp)
	clang++ -g -c -o rpanel.o $(WX_INCLUDE_PATH) -I../include ../src/rpanel.cpp

clean:
	rm *.o actrac