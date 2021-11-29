C++ = g++

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = $(shell root-config --libs)

Target = ReadNearlineTrees.exe

all:$(Target)

ReadNearlineTrees.exe: ReadNearlineTrees.C
	${C++} -o $@ ReadNearlineTrees.C $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

clean:
	rm *exe
