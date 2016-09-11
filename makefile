game: game.cpp Sprite.h Scene.h
	g++ -Werror -Wall -Wextra -pedantic -std=c++1z -o game game.cpp -lncurses

run:
	./game
