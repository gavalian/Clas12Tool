#INCCORE := $(C12CORE)/inc
LIBCORE := $(C12CORE)

#INCClas := $(C12CLAS12)/inc
LIBClas := $(C12CLAS12)

#INCRoot := $(C12RTOOL)/inc
LIBRoot := $(C12RTOOL)

#INCTools := $(C12TOOLS)/inc
LIBTools := $(C12TOOLS)

INCHIPO := $(HIPO)
LIBHIPO := $(CLAS12TOOL)/lib


ROOT := $(shell root-config --cflags) $(shell root-config --libs) -lEG

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CFLAGS  := -Wall -O2 -fPIC -std=c++14

CFLAGS := $(ROOT) $(CFLAGS)

INCLUDES := -I$(CLAS12CPPBASE)/includes -I$(INCHIPO)
LIBS :=	-L$(LIBClas) \
				-L$(LIBRoot) \
			  -L$(LIBCORE) \
        -L$(LIBTools) \
				-L$(LIBHIPO) \
				-lClas12 -lRootTools -lTools -lC12Core  -lhipo
  

all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp Makefile
	g++ $(DEBUG) $< -o $@  -I. $(INCLUDES) $(LIBS) $(ROOT) $(CFLAGS) 
