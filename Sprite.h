#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <map>
#include <utility>
#include <iostream>

template <typename T>
using Vec2 = std::pair<T, T>;

struct Sprite {
	Sprite(Vec2<unsigned> d, std::string s)
		: dimensions(d)
		, sheet(s)
	{}
	Vec2<unsigned> dimensions;
	std::string sheet;

	char get(unsigned x, unsigned y) const {
		return sheet.at(x*dimensions.second + y);
	}
	static constexpr char transparent = 'E';
};

struct SpriteSheet {
	SpriteSheet(std::map<std::string, Sprite> s)
		: sheets(s)
	{}
	std::map<std::string, Sprite> sheets;
};

const Sprite cactusSprite(Vec2<unsigned>(16, 28),
"          _-----_           "
" ________,_______,_________ "
"(                          )"
" ; _-------------------_ ,; "
"  `------|        |-----'   "
"         |  '   ' |    ,---,"
",----,   | ###  ###    |   }"
"{  ' |  #############  |   |"
"|'  '|   |  ##  ##|----   '|"
"{    ----|        }        }"
"| '    '   ' '  ' | '   '  |"
"{   '             |----+---'"
" `-+--'--|  '   ' |    '    "
"   '     {   '    }         "
"         | '   '  |         "
"         |'  '   '|         "
);

const Sprite cactusSprite2(Vec2<unsigned>(16, 28),
"EEEEEEEEEE_-----_EEEEEEEEEEE"
" ________,_______,_________ "
"(                          )"
"E; _-------------------_ ,;E"
"EE`------|        |-----'EEE"
"EEEEEEEEE|  '   ' |EEEE,---,"
",----,EEE| ###  ###EEEE|   }"
"{  ' |EE#############EE|   |"
"|'  '|EEE|  ##  ##|----   '|"
"{    ----|        }        }"
"| '    '   ' '  ' | '   '  |"
"{   '             |----+---'"
"E`-+--'--|  '   ' |EEEE'EEEE"
"EEE'EEEEE{   '    }EEEEEEEEE"
"EEEEEEEEE| '   '  |EEEEEEEEE"
"EEEEEEEEE|'  '   '|EEEEEEEEE"
);

#endif
