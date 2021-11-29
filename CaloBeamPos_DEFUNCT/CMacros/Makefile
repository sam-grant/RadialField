C++ = g++

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = $(shell root-config --libs)

Target = PlotBeamYPosVsRun.exe

all:$(Target)

PlotBeamYPosVsRun.exe: PlotBeamYPosVsRun.C
	${C++} -o $@ PlotBeamYPosVsRun.C $(Objects) $(ROOTFLAGS) $(ROOTLIBS) 
	
clean:
	rm *exe
