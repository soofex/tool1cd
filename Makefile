CFLAGS=-std=c++11 -Wfatal-errors -fpermissive -ISystemClasses -g -pg
LDFLAGS=-LSystemClasses -ldmpassystem -lboost_regex -lboost_filesystem -lboost_system -lz -g -pg

.cpp.o:
	g++ $(CFLAGS) -o $@ -c $<

all: SystemClasses/libdmpassystem.a tool

tool: cTool_1CD_Main.o ParseCommandLine.o MessageRegistration.o Class_1CD.o Common.o ConfigStorage.o Parse_tree.o \
	APIcfBase.o TempStream.o Base64.o UZLib.o
	g++ -o $@ $? $(LDFLAGS)

SystemClasses/libdmpassystem.a:
	make -C SystemClasses

clean:
	rm *.o
	rm tool