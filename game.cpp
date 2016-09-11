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
		return Vec2<unsigned>(m_pos.x, m_pos.y);
	}

	Sprite getSprite() const {
		if (m_attackTimer > 4*FPS/5)
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
				--m_pos.x;
				break;
			case Command::down:
				++m_pos.x;
				break;
			case Command::left:
				m_velocity.y -= 10;
				break;
			case Command::right:
				m_velocity.y += 10;
				break;
			case Command::attack:
				m_attackTimer = FPS * 1;
			default:
				break;
		}
	}

	void update() {
		m_pos += (m_velocity / FPS);
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
		m_sceneSize.x = m_picture.size();
		m_sceneSize.y = m_picture.front().length();
	}

	string getFrame(Vec2<int> frameStart) const {
		string ret = "";
		for (unsigned x = frameStart.x, xEnd = min(m_sceneSize.x, x + Height); x < xEnd; ++x) {
			for (unsigned y = frameStart.y, yEnd = min(m_sceneSize.y, y + Width); y < yEnd; ++y)
				ret += m_picture.at(x).at(y);
			ret += '\n';
		}
		replace(ret.begin(), ret.end(), 'E', ' ');
		return ret;
	}

	void draw(const Vec2<int> pos, const char c) {
		m_picture.at(pos.x).at(pos.y) = c;
	}

	void draw(const Vec2<int> pos, const Sprite sprite) {
		Vec2<int> d = sprite.dimensions;
		// preventing going out of the scene
		Vec2<int> diff = (d + pos) - m_sceneSize;
		if (diff.x > 0)
			d.x -= diff.x;
		if (diff.y > 0)
			d.x -= diff.y;
		for (int x = max(0, -pos.x); x < d.x; ++x)
			for (int y = max(0, -pos.y); y < d.y; ++y)
				if (sprite.get(x, y) != Sprite::transparent)
					m_picture.at(x+pos.x).at(y+pos.y) = sprite.get(x, y);
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
		printw(copy.getFrame({0, max(0, (int)(m_player.getFramePos().y) - 50)}).c_str());
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
