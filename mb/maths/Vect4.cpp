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

#include "Vect4.hpp"

namespace mb
{
    Vect4::Vect4(float x, float y, float z, float a)
    {
        this->_values.resize(4);
        this->_values[0] = x;
        this->_values[1] = y;
        this->_values[2] = z;
        this->_values[3] = a;
    }
    float Vect4::x() const
    {
        return this->_values[0];
    }
    void Vect4::x(const float& v)
    {
        this->_values[0] = v;
    }
    float Vect4::y() const
    {
        return this->_values[1];
    }
    void Vect4::y(const float& v)
    {
        this->_values[1] = v;
    }
    float Vect4::z() const
    {
        return this->_values[2];
    }
    void Vect4::z(const float& v)
    {
        this->_values[2] = v;
    }
    float Vect4::w() const
    {
        return this->_values[3];
    }
    void Vect4::w(const float& v)
    {
        this->_values[3] = v;
    }
	std::ostream& operator<<(std::ostream& str, const Vect4& v)
	{
		str << "Vect4(";
		str << v._values[0] << ", " << v._values[1] << ", "
			<< v._values[2] << ", " << v._values[3];
		str << ")";
		return str;
	}
}
