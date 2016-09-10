#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
using namespace std;

int main() {
	initscr();
	input = getch();
	endwin();

	return 0;
}
