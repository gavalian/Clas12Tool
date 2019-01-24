ROOTCFLAGS  := $(shell root-config --cflags)
ROOTLDFLAGS := $(shell root-config --ldflags)
ROOTLIBS    := $(shell root-config --libs) -lEG
ROOTGLIBS   := $(shell root-config --glibs)

HIPOCFLAGS  := -I../Hipo4
#HIPOLIBS    := -L../lib -lhipo4 -lclas12banks
HIPOLIBS    := -L../lib -lhipo4

LZ4LIBS     := -L../Lz4/lib -llz4
LZ4INCLUDES := -I../Lz4/lib

CXX       := g++
CXXFLAGS  += -Wall -fPIC $(ROOTCFLAGS)
LD        := g++
LDFLAGS   := $(ROOTLDFLAGS)


all: readRecords

readRecords: readRecords.o
	$(CXX) -o readRecords $< $(ROOTCFLAGS) $(ROOTLDFLAGS) $(HIPOLIBS) $(LZ4LIBS) $(ROOTLIBS)

#readParticles: readParticles.o
#	$(CXX) -o readParticles $< $(ROOTCFLAGS) $(ROOTLDFLAGS) $(HIPOLIBS) $(LZ4LIBS) $(ROOTLIBS)

#analysis: analysis.o
#	$(CXX) -o analysis $< $(ROOTCFLAGS) $(ROOTLDFLAGS) $(HIPOLIBS) $(LZ4LIBS) $(ROOTLIBS)

#clas12event_example: clas12event_example.o
#	$(CXX) -o clas12event_example $< $(ROOTCFLAGS) $(ROOTLDFLAGS) $(HIPOLIBS) $(LZ4LIBS) $(ROOTLIBS)

clean:
	@echo 'Removing all build files'
	@rm -rf *.o readParticles readBanks analysis clas12event_example *~

%.o: %.cc
	$(CXX) -c $< -O2 $(ROOTCFLAGS) $(HIPOCFLAGS) $(LZ4INCLUDES)
