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
#include "Vect2.hpp"

namespace MB
{
	Vect2::Vect2(float x, float y)
	{
        this->_values.resize(2);
        this->_values[0] = x;
        this->_values[1] = y;
	}
	float Vect2::x() const
	{
        return this->_values[0];
	}
	void Vect2::x(const float& v)
	{
        this->_values[0] = v;
	}
	float Vect2::y() const
	{
        return this->_values[1];
	}
	void Vect2::y(const float& v)
	{
        this->_values[1] = v;
	}
	bool Vect2::operator!=(const Vect2& v)
	{
		return !(*this == v);
	}
	bool Vect2::operator==(const Vect2& v)
	{
		return x() == v.x() && y() == v.y();
	}
}
