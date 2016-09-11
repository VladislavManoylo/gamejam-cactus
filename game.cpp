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

template<unsigned Width, unsigned Height>
class Canvas {
public:
	Canvas()
	{
		for (unsigned x = 0; x < Height; ++x) {
			for (unsigned y = 0; y < Width; ++y)
				m_picture[x][y] = '.';
			m_picture[x][Width] = '\n';
		}
	}

	const char* getPicture() const {
		return (char*)m_picture;
	}

	void set(Vec2<unsigned> pos, char c) {
		m_picture[pos.first][pos.second] = c;
	}
private:
	char m_picture[Height][Width+1]; // +1 for '\n' character
};

class Game {
public:
	Game()
		: m_running(true)
	{}

	bool isRunning() const { return m_running; }

	void print() const {
		Canvas<80, 30> copy = m_background;
		copy.set(m_player.getFramePos(), 'X');

		erase();
		printw(copy.getPicture());
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
	Canvas<80, 30> m_background;
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
