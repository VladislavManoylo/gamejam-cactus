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
		return sheet.at(x*dimensions.first + y);
	}
};

struct SpriteSheet {
	SpriteSheet(std::map<std::string, Sprite> s)
		: sheets(s)
	{}
	std::map<std::string, Sprite> sheets;
};

// note '€' is transparent
const Sprite cactusSprite(Vec2<unsigned>(28, 16),
"€€€€€€€€€€_-----_€€€€€€€€€€€"
" ________,_______,_________ "
"(                          )"
"€; _-------------------_ ,;€"
"€€`------|        |-----'€€€"
"€€€€€€€€€|  '   ' |€€€€,---,"
",----,€€€| ###  ###€€€€|   }"
"{  ' |€€#############€€|   |"
"|'  '|€€€|  ##  ##|----   '|"
"{    ----|        }        }"
"| '    '   ' '  ' | '   '  |"
"{   '             |----+---'"
"€`-+--'--|  '   ' |€€€€'€€€€"
"€€€'€€€€€{   '    }€€€€€€€€€"
"€€€€€€€€€| '   '  |€€€€€€€€€"
"€€€€€€€€€|'  '   '|€€€€€€€€€"
);

#endif
