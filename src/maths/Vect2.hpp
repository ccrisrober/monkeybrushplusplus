/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal
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

#ifndef __MB_VECT2__
#define __MB_VECT2__

#include <vector>

namespace MB
{
	class Vect2
	{
	public:
		Vect2(float x = 0.0f, float y = 0.0f)
		{
			this->_value.resize(2);
			this->_value[0] = x;
			this->_value[1] = y;
		}
		float x() const
		{
			return this->_value[0];
		}
		void x(const float& v)
		{
			this->_value[0] = v;
		}
		float y() const
		{
			return this->_value[1];
		}
		void y(const float& v)
		{
			this->_value[1] = v;
		}
	protected:
		std::vector<float> _value;
	};
}

#endif /* __MB_VECT2__ */