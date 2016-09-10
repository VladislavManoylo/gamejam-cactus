#include <iostream>
#include <chrono>
#include <thread>
#include <ncurses.h>
using namespace std;
using namespace std::chrono;

#define DEBUG

const unsigned FPS = 30;
const unsigned MPF = 1000/FPS;

enum class Command {
	exit,
	none
};

Command getCommand() {
	char input = getch();
	switch (input) {
		case 27: return Command::exit; // 27 is the escape key
		default: return Command::none;
	}
}

int main() {
	initscr();
	nodelay(stdscr, TRUE);
	Command cmd = Command::none;
	time_point<system_clock> time = system_clock::now();
	do {
		cmd = getCommand();
		time += milliseconds(MPF);
		this_thread::sleep_until(time);
#ifdef DEBUG
		if (cmd == Command::none)
			cerr << ". ";
#endif
		if (cmd == Command::exit)
			break;
	} while (true);
	endwin();

	return 0;
}
