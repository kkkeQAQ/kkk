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
#ifndef KOBJECT_H
#define KOBJECT_H

#include <unordered_set>
#include "KEvent.h"

class KObject{
private:
	KObject *parentP=nullptr;
	std::unordered_set<KObject*> childrenSet;
public:
	KObject(KObject *parent=nullptr);
	KObject(const KObject &object)=delete;
	virtual ~KObject();
	virtual void event(KEvent *event);
	void setParent(KObject *parent);
	KObject *parent();
	std::unordered_set<KObject*>& children();
};

#endif //KOBJECT_H
