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
	attack,
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
		case 'e': return Command::attack;
		default: return Command::none;
	}
}

class Character {
public:
	Vec2<unsigned> getFramePos () const {
		return Vec2<unsigned>(m_pos.first, m_pos.second);
	}

	Sprite getSprite() const {
		if (m_attackTimer > FPS)
			return saguero.at("attack1");
		if (m_attackTimer > FPS/2)
			return saguero.at("attack2");
		if (m_attackTimer > FPS/3)
			return saguero.at("attack1");
		return saguero.at("idle");
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
			case Command::attack:
				m_attackTimer = FPS * 1.2;
			default:
				break;
		}
	}

	void update() {
		m_pos.first += m_velocity.first / FPS;
		m_pos.second += m_velocity.second / FPS;
		if (m_attackTimer > 0)
			--m_attackTimer;
	}

private:
	unsigned m_attackTimer = 0;
	Vec2<double> m_pos = Vec2<double>(30, 30);
	Vec2<double> m_velocity = Vec2<double>(0,0);
};

template<unsigned Width, unsigned Height>
class Canvas {
public:
	Canvas()
	{
		m_picture = scene1;
		/* m_sceneSize.first = m_picture.size(); */
		/* m_sceneSize.second = m_picture.front().length(); */
		m_sceneSize.first = Height;
		m_sceneSize.second = Width;
	}

	string getFrame(Vec2<unsigned> frameStart) const {
		string ret = "";
		for (unsigned x = frameStart.first, xEnd = x + Height; x < xEnd; ++x) {
			for (unsigned y = frameStart.second, yEnd = y + Width; y < yEnd; ++y)
				ret += m_picture.at(x).at(y);
			ret += '\n';
		}
		replace(ret.begin(), ret.end(), 'E', ' ');
		return ret;
	}

	void draw(const Vec2<unsigned> pos, const char c) {
		m_picture.at(pos.first).at(pos.second) = c;
	}

	void draw(const Vec2<int> pos, const Sprite sprite) {
		Vec2<int> d = sprite.dimensions;
		// preventing going out of the scene
		int hDiff = (d.first + pos.first) - m_sceneSize.first;
		if (hDiff > 0)
			d.first -= hDiff;
		int wDiff = (d.second + pos.second) - m_sceneSize.second;
		if (wDiff > 0)
			d.first -= wDiff;
		for (int x = max(0, -pos.first); x < d.first; ++x)
			for (int y = max(0, -pos.second); y < d.second; ++y)
				if (sprite.get(x, y) != Sprite::transparent)
					m_picture.at(x+pos.first).at(y+pos.second) = sprite.get(x, y);
	}

private:
	Vec2<unsigned> m_sceneSize;
	vector<string> m_picture;
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
		printw(copy.getFrame({0, max(0, (int)m_player.getFramePos().second - 50)}).c_str());
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
		erase();
		printw("GAME OVER");
		refresh();
		this_thread::sleep_until(system_clock::now() + milliseconds(1000));
	}
	endwin();

	return 0;
}
