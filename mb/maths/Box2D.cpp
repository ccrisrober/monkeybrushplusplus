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

#include "Box2D.hpp"

namespace MB
{
	Box2D::Box2D(const Vect2& min, const Vect2& max)
	{
		this->_min = min;
		this->_max = max;
		this->_center = Vect2::add(this->_min, this->_max).scale(0.5f);
	}
	Vect2 Box2D::min() const
	{
		return this->_min;
	}
	Vect2 Box2D::max() const
	{
		return this->_max;
	}
	Vect2 Box2D::center() const
	{
		return this->_center;
	}
	Vect2 Box2D::size() const
	{
		return Vect2::sub(this->max(), this->min());
	}
	bool Box2D::containtsPoint(const Vect2& p)
	{
		if (p.x() > this->_min.x() || p.x() < this->_max.x() ||
			p.y() > this->_min.y() || p.y() < this->_max.y())
		{
			return true;
		}
		return false;
	}
	bool Box2D::containsBox(const Box2D& b)
	{
		if ((this->_min.x() <= b._min.x()) && (b._max.x() <= this->_max.x()) &&
			(this->_min.y() <= b._min.y()) && (b._max.y() <= this->_max.y()))
		{
			return true;
		}
		return false;
	}
	bool Box2D::intersectsBox(const Box2D& b)
	{
		if (b._max.x() < this->_min.x() || b._min.x() > this->_max.x() ||
			b._max.y() < this->_min.y() || b._min.y() > this->_max.y())
		{
			return false;
		}
		return true;
	}
	bool Box2D::isEqual(const Box2D& b)
	{
		return b.min() == this->_min && b.max() == this->_max;
	}
}
