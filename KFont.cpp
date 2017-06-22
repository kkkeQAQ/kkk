/**
 * Copyright (C) 2017 kkkeQAQ <kkke@nwsuaf.edu.cn>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/
#include "KFont.h"

std::unordered_map<std::pair<KFont::Color,KFont::Color>,int> KFont::colors;

int KFont::getColorNumber()
{
	auto pair=std::make_pair(foreground,background);
	auto it=colors.find(pair);
	if(it==colors.end())
	{
		int number=colors.size()+1;
		init_pair(number,foreground,background);
		colors.emplace(pair,number);
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
	this->background=BLACK;
	this->foreground=WHITE;
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
	return foreground;
}

KFont::Color KFont::getBg()const
{
	return background;
}

int KFont::getStyle()const
{
	return style;
}

namespace std
{
		hash<pair<KFont::Color,KFont::Color>>::result_type 
			hash<pair<KFont::Color,KFont::Color>>::operator()
			(const argument_type &a) const
			{
				result_type h=0;
				h^= std::hash<int>()((int)a.first) + 0x9e3779b9 + (h<< 6) + (h>> 2);
				h^= std::hash<int>()((int)a.second) + 0x9e3779b9 + (h<< 6) + (h>> 2);
				return h;
			}

}
