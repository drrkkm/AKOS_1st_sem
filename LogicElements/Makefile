TARGET = main

LIB_DIR = .

SOURCES = $(wildcard ${LIB_DIR}/Graph_lib/*.cpp) \
          Graph_ext.cpp \
          logic_shapes.cpp \
          logic.cpp \
          main.cpp

OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))


CXX ?= g++
CXXFLAGS := -std=c++17 -pedantic -Wall -Wextra -I${LIB_DIR} \
            $(patsubst -I%,-isystem%,$(shell fltk-config --use-images --cxxflags))
LDFLAGS  := $(shell fltk-config --use-images --ldflags)


.DEFAULT_GOAL := all
.PHONY: all clean clean-all


$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp %.h
	$(CXX) -c $(CXXFLAGS) -o $@ $<


all: $(TARGET)


clean:
	rm -f $(OBJECTS)

clean-all: clean
	rm -f $(TARGET)