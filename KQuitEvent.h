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
#ifndef KQUITEVENT_H
#define KQUITEVENT_H

#include "KEvent.h"

class KQuitEvent : public KEvent {
public:
	int exitCode;
	KQuitEvent(int exitCode):exitCode(exitCode)
	{
	}
	EventType type()override
	{
		return QuitEvent;
	}
};

#endif //KQUITEVENT_H
