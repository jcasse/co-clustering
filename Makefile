SRCDIR      := src
BUILDDIR    := build
TARGET      := bin/co-cluster

SOURCES     := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))

CC          := g++
CFLAGS      := -std=gnu++11 -Wall

LIB         :=
INC         := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@echo " Compiling..."
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."
	$(RM) $(BUILDDIR)/* $(TARGET)

tests:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

.PHONY: clean
