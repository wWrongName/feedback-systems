CC=g++
EXE=fsys
CFLAGS=-c -Wall -std=c++17
SOURCES=system.cpp interface.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $<

$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

clr:
	rm -rf *.o $(EXE)