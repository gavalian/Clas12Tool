ROOTCFLAGS  := $(shell root-config --cflags)
ROOTLDFLAGS := $(shell root-config --ldflags)
ROOTLIBS    := $(shell root-config --libs) -lEG
ROOTGLIBS   := $(shell root-config --glibs)

HIPOCFLAGS  := -I../Hipo -I../Banks
HIPOLIBS    := -L../lib -lhipo4 

LZ4LIBS     := -L../Lz4/lib -llz4
LZ4INCLUDES := -I../Lz4/lib

F77        = gfortran
CXX       := g++
CXXFLAGS  += -Wall -fPIC $(ROOTCFLAGS)
LD        := g++
LDFLAGS   := $(ROOTLDFLAGS)

CERNINCLUDES = -I$(CERN_ROOT)/include/cfortran
CERNLIBS     = -L$(CERN_ROOT)/lib -lpacklib -lgfortran
CERNFLAGS    = -w -Df2cFortran

all: freader

writeROOT: writeROOT.o
	$(CXX) -o writeROOT $< $(ROOTCFLAGS) $(ROOTLDFLAGS) $(HIPOLIBS) $(LZ4LIBS) $(ROOTLIBS)

showDictionary: showDictionary.o
	$(CXX) -o showDictionary $< $(ROOTCFLAGS) $(ROOTLDFLAGS) $(HIPOLIBS) $(LZ4LIBS) $(ROOTLIBS)

freader: freader.o
	$(CXX) -o freader $< $(ROOTCFLAGS) $(ROOTLDFLAGS) $(HIPOLIBS) $(LZ4LIBS)

fwriter: fwriter.cc
	$(CXX)  -o fwriter $< $(CERNFLAGS) $(CERNINCLUDES) $(CERNLIBS)

fort_reader: fort_reader.o
	$(F77) -o freader.exe fort_reader.o -lgcc -lstdc++ ../lib/libhipo4.a ../lib/liblz4.a

clean:
	@echo 'Removing all build files'
	@rm -rf *.o writeROOT showDictionary *~ fwriter freader
#=====================================================================
# COMPILE RULES
#=====================================================================
%.o: %.cc
	$(CXX) -c $<  -O2 $(ROOTCFLAGS) $(HIPOCFLAGS) $(LZ4INCLUDES)

%.o:%.F
	$(F77) -c $<
