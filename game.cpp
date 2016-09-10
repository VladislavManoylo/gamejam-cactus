#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
using namespace std;

#define DEBUG

enum class Command {
	exit,
	unknown
};

Command getCommand() {
	char input = getch();
	switch (input) {
		case 27: return Command::exit; // 27 is the escape key
		default: return Command::unknown;
	}
#ifdef DEBUG
	cerr << input << '\n';
#endif
}

int main() {
	initscr();
	Command cmd = Command::unknown;
	do {
		cmd = getCommand();
	} while (cmd != Command::exit);
	endwin();

	return 0;
}
