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

#ifndef __MB_CUSTOM_PING_PONG__
#define __MB_CUSTOM_PING_PONG__

#include <mb/api.h>

#include <functional>

namespace mb
{
	template <typename T>
	class CustomPingPong
	{
	public:
		CustomPingPong(const T & elem1, const T & elem2)
			: _elem1(std::move(elem1))
			, _elem2(std::move(elem2))
		{
		}
		void swap()
		{
			std::swap(_elem1, _elem2);
		}
		void swap(std::function<void()> cb)
		{
			std::swap(_elem1, _elem2);
			if (cb)
			{
				cb();
			}
		}
		T first() const
		{
			return _elem1;
		}
		T last() const
		{
			return _elem2;
		}
	protected:
		T _elem1;
		T _elem2;
	};
}

#endif /* __MB_CUSTOM_PING_PONG__ */
