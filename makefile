game: game.cpp
	g++ -Werror -Wall -Wextra --std=c++11 -o game game.cpp -lncurses

run:
	./game
