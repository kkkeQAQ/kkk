#ifndef KFONT_H
#define KFONT_H

#include <unordered_map>
#include "curses.h"

class KFont;

namespace std
{
		template<>
			struct hash<KFont>
			{
				typedef KFont argument_type;
				typedef std::size_t result_type;

				result_type operator()(const argument_type&a) const;
			};

}

class KFont{
public:
	enum Color {
		DEFAULT=-1,
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
	KFont(Color fg=DEFAULT,Color bg=DEFAULT,int style=0);
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
	KFont& reset();
	KFont& setFg(Color fg=DEFAULT);
	KFont& setBg(Color bg=DEFAULT);
	KFont& setStyle(int style);
	Color getFg()const;
	Color getBg()const;
	int getStyle()const;
	int getColorNumber();
private:
	Color foreground;
	Color background;
	int style;
	static std::unordered_map<KFont,int> colors;
};

#endif //KFONT_H
