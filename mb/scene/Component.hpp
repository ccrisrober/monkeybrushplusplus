/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus <https://github.com/maldicion069/monkeybrushplusplus>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef __MB_COMPONENT__
#define __MB_COMPONENT__

#include <mb/api.h>

#include <iostream>
#include <typeinfo>
#include <memory>

namespace MB
{
	class Node;
	class Component
	{
	public:
		MB_API
		Component();
		MB_API
		virtual void start() {}
		MB_API
		virtual void update(float /*dt*/);
		MB_API
		Node* getNode() const;
		MB_API
		void setNode(Node* n);
		MB_API
		friend std::ostream& operator<<(std::ostream & str, const Component& n)
		{
			str << typeid(n).name();
			return str;
		}
	protected:
		virtual ~Component() {}
		Node* _node;
	};
    // TODO: UNUSED typedef std::shared_ptr<Component> ComponentPtr;
}

#endif /* __MB_COMPONENT__ */
