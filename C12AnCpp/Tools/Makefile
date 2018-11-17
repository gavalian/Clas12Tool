INCDIR := inc
SRCDIR := src
OBJDIR := build

INCCORE := $(C12CORE)/inc
LIBCORE := $(C12CORE)

INCClas := $(C12CLAS12)/inc
LIBClas := $(C12CLAS12)

INCRoot := $(C12RTOOL)/inc
LIBRoot := $(C12RTOOL)


ROOT := $(shell root-config --cflags) $(shell root-config --libs)

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CFLAGS  := -Wall -O2 -fPIC -std=c++14

BUILD := $(shell mkdir -p build)

CFLAGS := $(ROOT) $(CFLAGS)

INCLUDES := -I$(INCCORE) -I$(INCClas) -I$(INCRoot) -I$(INCHIPO)
LIBS :=	-L$(LIBClas) \
				-L$(LIBRoot) \
			  -L$(LIBCORE) \
				-L$(LIBHIPO) \
				-lClas12 -lRootTools -lC12Core
  

.PHONY: all clean
all: $(BUILD) $(OBJECTS)
	$(CXX) $(DEBUG) -I$(INCDIR)  $(INCLUDES) $(LIBS) -o libTools.so -shared $(CFLAGS)  $(OBJECTS)	

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(DEBUG) $(CFLAGS) -I$(INCDIR)  $(INCLUDES) $(LIBS) -c $< -o $@

clean:
	rm build/*; rm libTools.so; rm -rf build
