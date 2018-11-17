INCCORE := $(C12CORE)/inc
LIBCORE := $(C12CORE)

INCClas := $(C12CLAS)/inc
LIBClas := $(C12CLAS)

INCRoot := $(C12RTOOL)/inc
LIBRoot := $(C12RTOOL)

INCTools := $(C12TOOLS)/inc
LIBTools := $(C12TOOLS)

INCHIPO := $(HIPO)
LIBHIPO := $(CLAS12TOOL)/lib


ROOT := $(shell root-config --cflags) $(shell root-config --libs) -lEG

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CFLAGS  := -Wall -O2 -fPIC -std=c++14

CFLAGS := $(ROOT) $(CFLAGS)

INCLUDES := -I$(INCCORE) -I$(INCClas) -I$(INCRoot) -I$(INCHIPO) -I$(INCTools)
LIBS :=	-L$(LIBClas) \
				-L$(LIBRoot) \
			  -L$(LIBCORE) \
        -L$(LIBTools) \
				-L$(LIBHIPO) \
				-lClas12 -lRootTools -lTools -lC12Core  -lhipo
  

all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp Makefile
	g++ $(DEBUG) $< -o $@ $(CFLAGS) -I. $(INCLUDES) $(LIBS) $(ROOT)
