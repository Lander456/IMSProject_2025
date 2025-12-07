CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2

LDFLAGS := -lX11 -lGL -lGLX -lpng -lpthread -ldl

TARGET := IMS

SRCS := \
    main.cpp \
    Species/SpeciesInfo.cpp \
    Species/SpeciesRegistry.cpp \
    Cell/Vegetation.cpp \
    Cell/Cell.cpp \
    Map/Map.cpp \
    Map/MapParser.cpp \
    ArgParser/ArgParser.cpp \
    Simulator/Simulator.cpp \
    Simulator/OutputWindow.cpp

OBJS := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)
	rm -f $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)
	rm -f $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run
