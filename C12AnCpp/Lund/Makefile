
INCDIR := inc
SRCDIR := src
OBJDIR := build

INCCORE := $(C12CORE)/inc
LIBCORE := $(C12CORE)

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CFLAGS  := -Wall -O2 -fPIC -std=c++14
INCLUDES := -I$(INCCORE)
LIBS := -L$(LIBCORE)

BUILD := $(shell mkdir -p build)

.PHONY: all clean
all: $(BUILD) $(OBJECTS)
	$(CXX) $(DEBUG) -I$(INCDIR)  $(INCLUDES) $(LIBS) -o libC12Lund.so -shared $(CFLAGS)  $(OBJECTS)	

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(DEBUG) $(CFLAGS) -I$(INCDIR) $(INCLUDES) $(LIBS) -c $< -o $@

clean:
	rm build/*; rm libC12Lund.so
