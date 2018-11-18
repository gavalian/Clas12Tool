#INCCORE := $(C12CORE)/inc
LIBCORE := $(C12CORE)

#INCClas := $(C12CLAS12)/inc
LIBClas := $(C12CLAS12)

#INCRoot := $(C12RTOOL)/inc
LIBRoot := $(C12RTOOL)

#INCTools := $(C12TOOLS)/inc
LIBTools := $(C12TOOLS)

#INCLUND := $(C12LUND)/inc
LIBLUND := $(C12LUND)

INCHIPO := $(HIPO)
LIBHIPO := $(CLAS12TOOL)/lib


ROOT := $(shell root-config --cflags) $(shell root-config --libs) -lEG

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CFLAGS  := -Wall -O2 -fPIC -std=c++14

CFLAGS := $(ROOT) $(CFLAGS)

INCLUDES := -I$(CLAS12CPPBASE)/includes -I$(INCHIPO)
LIBS :=	-L$(LIBClas) \
        -L$(LIBLUND) \
				-L$(LIBRoot) \
			  -L$(LIBCORE) \
        -L$(LIBTools) \
				-L$(LIBHIPO) \
				-lClas12 -lRootTools -lTools -lC12Core  -lhipo -lC12Lund
  

all:
	g++ $(DEBUG) -o ex_lund.exe ex_lund.cpp ex_lund_alg.cpp -I. $(INCLUDES) $(LIBS) $(ROOT) $(CFLAGS) 

