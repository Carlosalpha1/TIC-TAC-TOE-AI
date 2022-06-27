
OUT=tictactoe
CFLAGS = -Wall -Wshadow
LIBS = `pkg-config --cflags --libs sfml-graphics sfml-system sfml-window`
HEADERS = include
SRC = src/main.cpp src/game_entities.cpp src/game_brain.cpp

all:
	g++ -I $(HEADERS) -o $(OUT) $(CFLAGS) $(SRC) $(LIBS)

clean:
	rm $(OUT)