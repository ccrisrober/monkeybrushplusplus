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

#ifndef __MB_VECT4__
#define __MB_VECT4__

#include <vector>

namespace MB
{
	class Vect4
    {
	public:
        Vect4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float a = 1.0f)
        {
            this->_value.resize(4);
            this->_value[0] = x;
            this->_value[1] = y;
            this->_value[2] = z;
            this->_value[4] = a;
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
        float z() const
        {
            return this->_value[2];
        }
        void z(const float& v)
        {
            this->_value[2] = v;
        }
        float w() const
        {
            return this->_value[3];
        }
        void w(const float& v)
        {
            this->_value[3] = v;
        }
	protected:
		std::vector<float> _value;
	};
}

#endif /* __MB_VECT4__ */
