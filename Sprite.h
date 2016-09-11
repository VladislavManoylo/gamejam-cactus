#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <map>
#include <utility>
#include <iostream>

template<typename T>
struct Vec2 {

	Vec2() : x(0), y(0) {}
	Vec2(T x2, T y2) : x(x2), y(y2) {}

	template<typename U>
	Vec2(const Vec2<U>& other) : x(other.x), y(other.y) {}

	Vec2& operator+= (const Vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	Vec2& operator-= (const Vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vec2& operator*= (const int scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}
	Vec2& operator/= (const int scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}

	Vec2 operator+ (Vec2 other) const {
		other += *this;
		return other;
	}
	Vec2 operator- (Vec2 other) const {
		other -= *this;
		return -other;
	}
	Vec2 operator* (const int scalar) const {
		return Vec2(x*scalar, y*scalar);
	}
	Vec2 operator/ (const int scalar) const {
		return Vec2(x/scalar, y/scalar);
	}
	Vec2 operator-() const {
		Vec2 ret(-x,-y);
		return ret;
	}

	friend std::ostream& operator<<(std::ostream& out, const Vec2& vec) {
		out << '(' << vec.x << ", " << vec.y << ')';
		return out;
	}


	T x;
	T y;
};

struct Sprite {
	Sprite(Vec2<unsigned> d, std::string s)
		: dimensions(d)
		, sheet(s)
	{}
	Vec2<unsigned> dimensions;
	std::string sheet;

	char get(unsigned x, unsigned y) const {
		return sheet.at(x*dimensions.y + y);
	}
	static constexpr char transparent = 'E';
};


using SpriteSheet = std::map<std::string, Sprite>;

const SpriteSheet saguero = {
{"idle", {Vec2<char>(16, 46),
"EEEEEEEEEEEEEEEEEEE_-----_EEEEEEEEEEEEEEEEEEEE"
"EEEEEEEEE ________,_______,_________ EEEEEEEEE"
"EEEEEEEEE(                          )EEEEEEEEE"
"EEEEEEEEEE; _-------------------_ ,;EEEEEEEEEE"
"EEEEEEEEEEE`------|        |-----'EEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE|  '   ' |EEEE,---,EEEEEEEEE"
"EEEEEEEEE,----,EEE| ###  ###EEEE|   }EEEEEEEEE"
"EEEEEEEEE{  ' |EE#############EE|   |EEEEEEEEE"
"EEEEEEEEE|'  '|EEE|  ##  ##|----   '|EEEEEEEEE"
"EEEEEEEEE{    ----|        }        }EEEEEEEEE"
"EEEEEEEEE| '    '   ' '  ' | '   '  |EEEEEEEEE"
"EEEEEEEEE{   '             |----,---'EEEEEEEEE"
"EEEEEEEEEE`-,--'--|  '   ' |EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE{   '    }EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE| '   '  |EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE|'  '   '|EEEEEEEEEEEEEEEEEE"
}},
{"attack1", {Vec2<char>(16, 46),
"EEEEEEEEEEEEEEEEEEE_-----_EEEEEEEEEEEEEEEEEEEE"
"EEEEEEEEE ________,_______,_________EEEEEEEEEE"
"EEEEEEEEE(                          )EEEEEEEEE"
"EEEEEEEEEE; _-------------------_ ,;EEEEEEEEEE"
"EEEEEEEEEEE`------|        |-----'EEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE|  '   ' |EEEEEEEE,,,,EEEEEE"
"EEEEEEEEE,----,EEE| ###  ###EEEEEEE/    \\EEEEE"
"EEEEEEEEE{  ' |EE#############EEEE,     'EEEEE"
"EEEEEEEEE|'  '|EEE|  ##  ##|-----' '   'EEEEEE"
"EEEEEEEEE{    ----|        }          'EEEEEEE"
"EEEEEEEEE| '    '   ' '  ' | '   '   'EEEEEEEE"
"EEEEEEEEE{   '             |----,-'''EEEEEEEEE"
"EEEEEEEEEE`-,--'--|  '   ' |EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE{   '    }EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE| '   '  |EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE|'  '   '|EEEEEEEEEEEEEEEEEE"
}},
{"attack2", {Vec2<char>(16, 46),
"EEEEEEEEEEEEEEEEEEE_-----_EEEEEEEEEEEEEEEEEEEE"
"EEEEEEEEE ________,_______,_________EEEEEEEEEE"
"EEEEEEEEE(                          )EEEEEEEEE"
"EEEEEEEEEE; _-------------------_ ,;EEEEEEEEEE"
"EEEEEEEEEEE`------|        |-----'EEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE|  '   ' |EEEEEEEEEEEEE,,,EE"
"EEEEEEEEE,----,EEE| ###  ###EEEEEEEEEE,''   ',"
"EEEEEEEEE{  ' |EE#############EEEEEE,'       ,"
"EEEEEEEEE|'  '|EEE|  ##  ##|-------'       ,'E"
"EEEEEEEEE{    ----|        }             ,'EEE"
"EEEEEEEEE| '    '   ' '  ' | '   '     ,'EEEEE"
"EEEEEEEEE{   '             |----,-'''''EEEEEEE"
"EEEEEEEEEE`-,--'--|  '   ' |EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE{   '    }EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE| '   '  |EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE|'  '   '|EEEEEEEEEEEEEEEEEE"
}}
};

const SpriteSheet sagueroReversed = {
{"idle", {Vec2<char>(16, 46),
"EEEEEEEEEEEEEEEEEEEE_-----_EEEEEEEEEEEEEEEEEEE"
"EEEEEEEEE _________,_______,________ EEEEEEEEE"
"EEEEEEEEE(                          )EEEEEEEEE"
"EEEEEEEEEE;, _-------------------_ ;EEEEEEEEEE"
"EEEEEEEEEEEE'-----|        |------`EEEEEEEEEEE"
"EEEEEEEEE,---,EEEE| '   '  |EEEEEEEEEEEEEEEEEE"
"EEEEEEEEE{   |EEEE###  ### |EEE,----,EEEEEEEEE"
"EEEEEEEEE|   |EE#############EE| '  }EEEEEEEEE"
"EEEEEEEEE|'   ----|##  ##  |EEE|'  '|EEEEEEEEE"
"EEEEEEEEE{        {        |----    }EEEEEEEEE"
"EEEEEEEEE|  '   ' | '  ' '   '    ' |EEEEEEEEE"
"EEEEEEEEE'---,----|             '   }EEEEEEEEE"
"EEEEEEEEEEEEEEEEEE| '   '  |--'--,-`EEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE{    '   }EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE|  '   ' |EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE|'   '  '|EEEEEEEEEEEEEEEEEE"
}},
{"attack1", {Vec2<char>(16, 46),
"EEEEEEEEEEEEEEEEEEEE_-----_EEEEEEEEEEEEEEEEEEE"
"EEEEEEEEEE_________,_______,________ EEEEEEEEE"
"EEEEEEEEE(                          )EEEEEEEEE"
"EEEEEEEEEE;, _-------------------_ ;EEEEEEEEEE"
"EEEEEEEEEEEE'-----|        |------`EEEEEEEEEEE"
"EEEEEE,,,,EEEEEEEE| '   '  |EEEEEEEEEEEEEEEEEE"
"EEEEE/    \\EEEEEEE###  ### |EEE,----,EEEEEEEEE"
"EEEEE'     ,EEEE#############EE| '  }EEEEEEEEE"
"EEEEEE'   ' '-----|##  ##  |EEE|'  '|EEEEEEEEE"
"EEEEEEE'          {        |----    }EEEEEEEEE"
"EEEEEEEE'   '   ' | '  ' '   '    ' |EEEEEEEEE"
"EEEEEEEEE'''-,----|             '   }EEEEEEEEE"
"EEEEEEEEEEEEEEEEEE| '   '  |--'--,-`EEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE{    '   }EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE|  '   ' |EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE|'   '  '|EEEEEEEEEEEEEEEEEE"
}},
{"attack2", {Vec2<char>(16, 46),
"EEEEEEEEEEEEEEEEEEEE_-----_EEEEEEEEEEEEEEEEEEE"
"EEEEEEEEEE_________,_______,________ EEEEEEEEE"
"EEEEEEEEE(                          )EEEEEEEEE"
"EEEEEEEEEE;, _-------------------_ ;EEEEEEEEEE"
"EEEEEEEEEEEE'-----|        |------`EEEEEEEEEEE"
"EE,,,EEEEEEEEEEEEE| '   '  |EEEEEEEEEEEEEEEEEE"
",'   '',EEEEEEEEEE###  ### |EEE,----,EEEEEEEEE"
",       ',EEEEEE#############EE| '  }EEEEEEEEE"
"E',       '-------|##  ##  |EEE|'  '|EEEEEEEEE"
"EEE',             {        |----    }EEEEEEEEE"
"EEEEE',     '   ' | '  ' '   '    ' |EEEEEEEEE"
"EEEEEEE'''''-,----|             '   }EEEEEEEEE"
"EEEEEEEEEEEEEEEEEE| '   '  |--'--,-`EEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE{    '   }EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE|  '   ' |EEEEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEEEEEEE|'   '  '|EEEEEEEEEEEEEEEEEE"
}}
};

#endif
