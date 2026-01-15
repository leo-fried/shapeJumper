# Define variables for easier maintenance
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = s
OBJS = main.o screen.o font.o properties.o

# Default target: builds the program by linking object files
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

# Rule to compile source files into object files
# This uses automatic variables:
# $@ is the target name (e.g., main.o)
# $< is the first prerequisite (e.g., main.cpp)
main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

screen.o: screen.cpp screen.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

font.o: font.cpp font.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

properties.o: properties.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Phony target for cleaning up generated files
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
