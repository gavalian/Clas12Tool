
INCDIR := inc
SRCDIR := src
OBJDIR := build

INCCORE := $(CORE)/inc
LIBCORE := $(CORE)

INCClas := $(CLAS)/inc
LIBClas := $(CLAS)


ROOT := $(shell root-config --cflags) $(shell root-config --libs)

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CFLAGS  := -Wall -O2 -fPIC -std=c++14

BUILD := $(shell mkdir -p build)

CFLAGS := $(ROOT) $(CFLAGS)

INCLUDES := -I$(INCCORE) -I$(INCClas)
LIBS := -L$(LIBCORE) -L$(LIBClas)

.PHONY: all clean
all: $(BUILD) $(OBJECTS)
	$(CXX) $(DEBUG) -I$(INCDIR)  $(INCLUDES) $(LIBS) -o libRootTools.so -shared $(CFLAGS)  $(OBJECTS)	

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(DEBUG) $(CFLAGS) -I$(INCDIR)  $(INCLUDES) $(LIBS) -c $< -o $@

clean:
	rm build/*; rm libRootTools.so; rm -rf build
