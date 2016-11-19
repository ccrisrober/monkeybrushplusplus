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

#ifndef __MB_VECT2__
#define __MB_VECT2__

#include <iostream>
#include <vector>

namespace MB
{
	class Vect2
	{
	public:
		Vect2(float x = 0.0f, float y = 0.0f);
		float x() const;
		void x(const float& v);
		float y() const;
		void y(const float& v);
        friend std::ostream& operator<<(std::ostream& str, const Vect2& v) {
            str << "Vect2(";
            str << v._values[0] << ", " << v._values[1];
            str << ")";
            return str;
        }
		bool operator!=(const Vect2& v)
		{
			return !(*this == v);
		}
		bool operator==(const Vect2& v)
		{
			return x() == v.x() && y() == v.y();
		}
    public:
        std::vector<float> _values;
	};
}

#endif /* __MB_VECT2__ */
