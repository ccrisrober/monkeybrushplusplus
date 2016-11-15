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

#ifndef __MB_COLOR4__
#define __MB_COLOR4__

#include "../maths/Vect4.hpp"

namespace MB {
	class Color4 {
	public:
		Color4(float r, float g, float b, float a)
		{
            this->_color = Vect4(r, g, b, a);
        }
        float r() const { return this->_color.x(); }
        float g() const { return this->_color.y(); }
        float b() const { return this->_color.z(); }
        float a() const { return this->_color.w(); }
        void r(const float v) { this->_color.x(v); }
        void g(const float v) { this->_color.y(v); }
        void b(const float v) { this->_color.z(v); }
        void a(const float v) { this->_color.w(v); }

	protected:
		Vect4 _color;
    };
}

#endif /* __MB_COLOR4__ */
