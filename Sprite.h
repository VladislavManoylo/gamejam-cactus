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


using SpriteSheet = std::map<std::string, Sprite>;
const SpriteSheet saguero = {

{"idle", {Vec2<unsigned>(16, 28),
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
"{   '             |----,---'"
"E`-,--'--|  '   ' |EEEEEEEEE"
"EEEEEEEEE{   '    }EEEEEEEEE"
"EEEEEEEEE| '   '  |EEEEEEEEE"
"EEEEEEEEE|'  '   '|EEEEEEEEE"
}},


{"attack1", {Vec2<unsigned>(16, 32),
"EEEEEEEEEE_-----_EEEEEEEEEEEEEEE"
" ________,_______,_________EEEEE"
"(                          )EEEE"
"E; _-------------------_ ,;EEEEE"
"EE`------|        |-----'EEEEEEE"
"EEEEEEEEE|  '   ' |EEEEEEEE,,,,E"
",----,EEE| ###  ###EEEEEEE/    \\"
"{  ' |EE#############EEEE,     '"
"|'  '|EEE|  ##  ##|-----' '   'E"
"{    ----|        }          'EE"
"| '    '   ' '  ' | '   '   'EEE"
"{   '             |----,-'''EEEE"
"E`-,--'--|  '   ' |EEEEEEEEEEEEE"
"EEEEEEEEE{   '    }EEEEEEEEEEEEE"
"EEEEEEEEE| '   '  |EEEEEEEEEEEEE"
"EEEEEEEEE|'  '   '|EEEEEEEEEEEEE"
}},

{"attack2", {Vec2<unsigned>(16, 37),
"EEEEEEEEEE_-----_EEEEEEEEEEEEEEEEEEEE"
" ________,_______,_________EEEEEEEEEE"
"(                          )EEEEEEEEE"
"E; _-------------------_ ,;EEEEEEEEEE"
"EE`------|        |-----'EEEEEEEEEEEE"
"EEEEEEEEE|  '   ' |EEEEEEEEEEEEE,,,EE"
",----,EEE| ###  ###EEEEEEEEEE,''   ',"
"{  ' |EE#############EEEEEE,'       ,"
"|'  '|EEE|  ##  ##|-------'       ,'E"
"{    ----|        }             ,'EEE"
"| '    '   ' '  ' | '   '     ,'EEEEE"
"{   '             |----,-'''''EEEEEEE"
"E`-,--'--|  '   ' |EEEEEEEEEEEEEEEEEE"
"EEEEEEEEE{   '    }EEEEEEEEEEEEEEEEEE"
"EEEEEEEEE| '   '  |EEEEEEEEEEEEEEEEEE"
"EEEEEEEEE|'  '   '|EEEEEEEEEEEEEEEEEE"
}}
};

#endif
