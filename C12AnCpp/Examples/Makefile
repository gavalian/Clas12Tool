INCCORE := $(CORE)/inc
LIBCORE := $(CORE)

INCClas := $(CLAS)/inc
LIBClas := $(CLAS)

INCRoot := $(TOOL)/inc
LIBRoot := $(TOOL)

INCHIPO := $(HIPO)
LIBHIPO := $(CLAS12TOOL)/lib


ROOT := $(shell root-config --cflags) $(shell root-config --libs) -lEG

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CFLAGS  := -Wall -O2 -fPIC -std=c++14

CFLAGS := $(ROOT) $(CFLAGS)

INCLUDES := -I$(INCCORE) -I$(INCClas) -I$(INCRoot) -I$(INCHIPO)
LIBS :=	-L$(LIBClas) \
				-L$(LIBRoot) \
			  -L$(LIBCORE) \
				-L$(LIBHIPO) \
				-lClas12 -lRootTools -lC12Core  -lhipo
  

all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp Makefile
	g++ $< -o $@ $(CFLAGS) -I. $(INCLUDES) $(LIBS) $(ROOT)
