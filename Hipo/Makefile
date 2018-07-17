
SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

LIBDIR  = ../lib
BINDIR  = ../bin

LZ4INCLUDES := -I../Lz4/lib/

libhipo: checkdirs $(OBJECTS)
	ar cr ../lib/libhipo.a $(OBJECTS)

show:
	@echo $(OBJECTS)

checkdirs: $(LIBDIR)

$(LIBDIR):
	@mkdir -p $(LIBDIR)

clean:
	@echo 'Removing the build files....'
	@rm -rf *~ *.o

%.o: %.cpp
	$(CXX) -c $< -O2 -D__LZ4__ $(LZ4INCLUDES)
