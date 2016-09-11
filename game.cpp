#include <iostream>
#include <chrono>
#include <thread>
#include <ncurses.h>

#include "Sprite.h"

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

class Character {
public:
	Vec2<unsigned> getFramePos () const {
		return m_pos;
	}

	Sprite getSprite() const {
		return cactusSprite2;
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
	Vec2<unsigned> m_pos = Vec2<unsigned>(30, 30);
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

	void draw(const Vec2<unsigned> pos, const char c) {
		m_picture[pos.first][pos.second] = c;
	}

	void draw(const Vec2<unsigned> pos, const Sprite sprite) {
		const Vec2<unsigned>& d = sprite.dimensions;
		for (unsigned x = 0; x < d.first; ++x)
			for (unsigned y = 0; y < d.second; ++y)
				if (sprite.get(x, y) != Sprite::transparent)
					m_picture[x+pos.first][y+pos.second] = sprite.get(x, y);
	}

private:
	char m_picture[Height][Width+1]; // +1 for '\n' character
};

template<unsigned Width, unsigned Height>
class Game {
public:
	Game()
		: m_running(true)
	{}

	bool isRunning() const { return m_running; }

	void print() const {
		Canvas<Width, Height> copy = m_background;
		/* copy.draw(m_player.getFramePos(), 'X'); */
		/* copy.draw(m_player.getFramePos(), Sprite(Vec2<unsigned>(2, 4), "12345678")); */
		copy.draw(m_player.getFramePos(), m_player.getSprite());

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
	Canvas<Width, Height> m_background;
};

int main() {
	try {
	initscr();
	nodelay(stdscr, TRUE);
	time_point<system_clock> time = system_clock::now();
	Game<200, 50> game;
	do {
		game.update();
		game.print();

		time += milliseconds(MPF);
		this_thread::sleep_until(time);
	} while (game.isRunning());
	}
	catch (...)
	{
	endwin();
	}

	return 0;
}
