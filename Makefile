
OUT=main
CFLAGS = -Wall -Wshadow
LIBS = `pkg-config --cflags --libs sfml-graphics sfml-system sfml-window`
SRC = main.cpp game_entities.cpp game_brain.cpp

all:
	g++ -o $(OUT) $(CFLAGS) $(SRC) $(LIBS)

clean:
	rm $(OUT)