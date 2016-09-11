#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <ncurses.h>

#include "Sprite.h"
#include "Scene.h"

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
		return Vec2<unsigned>(m_pos.first, m_pos.second);
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
				m_velocity.second = -10;
				break;
			case Command::right:
				m_velocity.second = 10;
				break;
			default:
				break;
		}
	}

	void update() {
		m_pos.first += m_velocity.first / FPS;
		m_pos.second += m_velocity.second / FPS;
	}

private:
	Vec2<double> m_pos = Vec2<double>(30, 30);
	Vec2<double> m_velocity = Vec2<double>(0,0);
};

template<unsigned Width, unsigned Height>
class Canvas {
public:
	Canvas()
	{
		m_picture.resize((Width+1)*Height);
		/* unsigned i = 0; */
		/* for (unsigned x = 0; x < Height; ++x) { */
		/* 	for (unsigned y = 0; y < Width; ++y) */
		/* 		m_picture[i++] = 'E'; */
		/* 	m_picture[i++] = '\n'; */
		/* } */
		m_picture = scene1;
	}

	string getPicture() const {
		string ret = m_picture;
		replace(ret.begin(), ret.end(), 'E', ' ');
		return ret;
	}

	void draw(const Vec2<unsigned> pos, const char c) {
		m_picture.at(m_getIndex(pos)) = c;
	}

	void draw(const Vec2<unsigned> pos, const Sprite sprite) {
		const Vec2<unsigned>& d = sprite.dimensions;
		for (unsigned x = 0; x < d.first; ++x)
			for (unsigned y = 0; y < d.second; ++y)
				if (sprite.get(x, y) != Sprite::transparent)
					m_picture.at(m_getIndex(x+pos.first, y+pos.second)) = sprite.get(x, y);
	}

private:
	unsigned m_getIndex(unsigned x, unsigned y) const { return x * (Width + 1) + y; }
	unsigned m_getIndex(Vec2<unsigned> pos) const { return m_getIndex(pos.first, pos.second); }
	string m_picture;
};

template<unsigned Width, unsigned Height>
class Game {
public:
	Game()
		: m_running(true)
	{ }

	bool isRunning() const { return m_running; }

	void print() const {
		Canvas<Width, Height> copy = m_background;
		copy.draw(m_player.getFramePos(), m_player.getSprite());

		erase();
		printw(copy.getPicture().c_str());
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
