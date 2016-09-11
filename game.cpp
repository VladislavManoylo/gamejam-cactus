#include <iostream>
#include <chrono>
#include <thread>
#include <utility>
#include <cstring>
#include <ncurses.h>
using namespace std;
using namespace std::chrono;

#define DEBUG

const unsigned FPS = 30;
const unsigned MPF = 1000/FPS;

enum class Command {
	up,
	down,
	left,
	right,
	exit,
	none
};

Command getCommand() {
	char input = getch();
	switch (input) {
		case 27: return Command::exit; // 27 is the escape key
		case 'w': return Command::up;
		case 'a': return Command::left;
		case 's': return Command::down;
		case 'd': return Command::right;
		default: return Command::none;
	}
}

template <typename T>
using Vec2 = pair<T, T>;

class Character {
public:
	Vec2<unsigned> getFramePos () const {
		return m_pos;
	}

	void runCommand(Command cmd) {
		switch (cmd) {
			case Command::up:
				--m_pos.first;
				break;
			case Command::down:
				++m_pos.first;
				break;
			case Command::left:
				--m_pos.second;
				break;
			case Command::right:
				++m_pos.second;
				break;
			default:
				break;
		}
	}

	void update() {
	}

private:
	Vec2<unsigned> m_pos;
};

class Game {
	using Pos = Vec2<unsigned>;
	unsigned posToIndex(Pos pos) const {
		return pos.first * m_frameWidth + pos.second;
	}
public:
	Game()
		: m_running(true)
	{}

	bool isRunning() const { return m_running; }

	void print() const {
		char frame[m_frameSize];
		strncpy(frame, m_background, m_frameSize);
		frame[posToIndex(m_player.getFramePos())] = 'X';

		erase();
		printw(frame);
		refresh();
	}

	void update() {
		m_runCommand(getCommand()); // calls runCommand on player
		m_player.update();
	}

private:

	void m_runCommand(Command cmd) {
		switch (cmd) {
			case Command::exit:
				m_running = false;
				break;
			case Command::none:
				break;
			default:
				m_player.runCommand(cmd);
		}
	}

private:
	Character m_player;
	bool m_running;
	static constexpr unsigned m_frameWidth = 81;
	static constexpr unsigned m_frameHeight = 31;
	static constexpr unsigned m_frameSize = m_frameWidth * m_frameHeight;
	char m_background[m_frameSize] =
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n"
		"................................................................................\n";
};

int main() {
	initscr();
	nodelay(stdscr, TRUE);
	time_point<system_clock> time = system_clock::now();
	Game game;
	do {
		game.update();
		game.print();

		time += milliseconds(MPF);
		this_thread::sleep_until(time);
	} while (game.isRunning());
	endwin();

	return 0;
}
