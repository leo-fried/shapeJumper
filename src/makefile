UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    SFML_INCLUDE = -I/opt/homebrew/include
    SFML_LIB = -L/opt/homebrew/lib
else
    SFML_INCLUDE =
    SFML_LIB =
endif


CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 $(SFML_INCLUDE)
LDFLAGS = -lncurses -lsfml-audio -lsfml-system $(SFML_LIB)
TARGET = shapeJumper
OBJS = main.o screen.o font.o properties.o level.o player.o ship.o ball.o sfx.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@
main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

screen.o: screen.cpp screen.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

font.o: font.cpp font.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

properties.o: properties.cpp properties.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

level.o: level.cpp level.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

player.o: player.cpp player.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

ship.o: ship.cpp ship.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

ball.o: ball.cpp ball.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

sfx.o: sfx.cpp sfx.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
