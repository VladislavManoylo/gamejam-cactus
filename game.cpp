#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
using namespace std;

int main() {
	initscr();
	char input = ' ';
	do {
		input = getch();
		erase();
		printw(&input);
		refresh();
	} while (input != 27); // 27 is the escape key
	endwin();

	return 0;
}
