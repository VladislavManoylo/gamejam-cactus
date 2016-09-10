#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <map>

struct Sprite {
	Sprite(unsigned w, unsigned h, unsigned std::vector<char> s)
		: width(w)
		, height(h)
		, sheet(s)
	{}
	unsigned width;
	unsigned height;
	std::vector<char> sheet;
}

struct SpriteSheet {
	SpriteSheet(std::map<std::string, Sprite> s)
		: sheets(s)
	{}
	std::map<std::string, Sprite> sheets;
}

// note '€' is transparent
const Sprite Cactus (28, 16,
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
)

#endif
