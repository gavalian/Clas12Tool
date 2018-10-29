
INCDIR := inc
SRCDIR := src
OBJDIR := build

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CFLAGS  := -Wall -O2 -fPIC -std=c++14

BUILD := $(shell mkdir -p build)


.PHONY: all clean
all: $(BUILD) $(OBJECTS)
	$(CXX) -I$(INCDIR) -o libC12Core.so -shared $(CFLAGS)  $(OBJECTS)	

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm build/*; rm libC12Core.so; rm -rf build
