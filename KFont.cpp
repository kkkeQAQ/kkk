#include "KFont.h"

int KFont::getColorNumber()
{
	auto it=colors.find(*this);
	if(it==colors.end())
	{
		int number=colors.size()+1;
		init_pair(number,foreground,background);
		colors.emplace(*this,number);
		return number;
	}
	else return it->second;
}

KFont::KFont(KFont::Color fg,KFont::Color bg,int style)
{
	foreground=fg;
	background=bg;
	this->style=style;
}

const KFont& KFont::operator+=(int style)
{
	this->style|=style;
	return *this;
}

const KFont& KFont::operator-=(int style)
{
	this->style&=~style;
	return *this;
}

const KFont& KFont::operator|=(int style)
{
	this->style|=style;
	return *this;
}

const KFont& KFont::operator&=(int style)
{
	this->style&=style;
	return *this;
}

const KFont& KFont::operator^=(int style)
{
	this->style^=style;
	return *this;
}

KFont operator+(const KFont &a,int b)
{
	return KFont(a)+=b;
}

KFont operator-(const KFont &a,int b)
{
	return KFont(a)-=b;
}

KFont operator|(const KFont &a,int b)
{
	return KFont(a)|=b;
}

KFont operator&(const KFont &a,int b)
{
	return KFont(a)&=b;
}

KFont operator^(const KFont &a,int b)
{
	return KFont(a)^=b;
}

KFont& KFont::reset()
{
	this->background=DEFAULT;
	this->foreground=DEFAULT;
	this->style=0;
	return *this;
}

KFont& KFont::setFg(KFont::Color fg)
{
	this->foreground=fg;
	return *this;
}

KFont& KFont::setBg(KFont::Color bg)
{
	this->background=bg;
	return *this;
}

KFont& KFont::setStyle(int style)
{
	this->style=style;
	return *this;
}

KFont::Color KFont::getFg()const
{
	if(foreground==DEFAULT)return DEFAULT;
	return foreground;
}

KFont::Color KFont::getBg()const
{
	if(background==DEFAULT)return DEFAULT;
	return background;
}

int KFont::getStyle()const
{
	return style;
}

namespace std
{
				hash<KFont>::result_type hash<KFont>::operator()(const argument_type &a) const
				{
					result_type h=0;
					h^= std::hash<int>()((int)a.getFg()) + 0x9e3779b9 + (h<< 6) + (h>> 2);
					h^= std::hash<int>()((int)a.getBg()) + 0x9e3779b9 + (h<< 6) + (h>> 2);
					h^= std::hash<int>()((int)a.getStyle()) + 0x9e3779b9 + (h<< 6) + (h>> 2);
					return h;
				}

}
