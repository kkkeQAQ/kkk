#ifndef KFONT_H
#define KFONT_H

#include <unordered_map>
#include "curses.h"

class KFont{
public:
	enum Color {
		BLACK	= COLOR_BLACK,
		RED		= COLOR_RED,
		GREEN	= COLOR_GREEN,
		YELLOW	= COLOR_YELLOW,
		BLUE	= COLOR_BLUE,
		PURPLE	= COLOR_MAGENTA,
		CYAN	= COLOR_CYAN,
		WHITE	= COLOR_WHITE,
	};
	enum Style{
		HIGHLIGHT		= A_STANDOUT,
		UNDERLINE		= A_UNDERLINE,
		BLINK			= A_BLINK,
		BOLD			= A_BOLD,
		BLANK			= A_INVIS,
	};
	KFont(Color fg=WHITE,Color bg=BLACK,int style=0);
	const KFont& operator+=(int style);
	const KFont& operator-=(int style);
	const KFont& operator|=(int style);
	const KFont& operator&=(int style);
	const KFont& operator^=(int style);
	friend KFont operator+(const KFont &a,int b);
	friend KFont operator-(const KFont &a,int b);
	friend KFont operator|(const KFont &a,int b);
	friend KFont operator&(const KFont &a,int b);
	friend KFont operator^(const KFont &a,int b);
	friend bool operator==(const KFont &a,const KFont &b);
	KFont& reset();
	KFont& setFg(Color fg=WHITE);
	KFont& setBg(Color bg=BLACK);
	KFont& setStyle(int style);
	Color getFg()const;
	Color getBg()const;
	int getStyle()const;
	int getColorNumber();
private:
	Color foreground;
	Color background;
	int style;
	static std::unordered_map<std::pair<Color,Color>,int> colors;
};

namespace std
{
		template<>
			struct hash<pair<KFont::Color,KFont::Color>>
			{
				typedef pair<KFont::Color,KFont::Color> argument_type;
				typedef std::size_t result_type;

				result_type operator()(const argument_type&a) const;
			};

}

#endif //KFONT_H
