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

#include "Box3D.hpp"

namespace mb
{
	Box3D::Box3D(const Vect3& min, const Vect3& max)
	{
		this->_min = min;
		this->_max = max;
		this->_center = Vect3::add(this->_min, this->_max).scale(0.5f);
	}
	Vect3 Box3D::min() const
	{
		return this->_min;
	}
	Vect3 Box3D::max() const
	{
		return this->_max;
	}
	Vect3 Box3D::center() const
	{
		return this->_center;
	}
	Vect3 Box3D::size() const
	{
		return Vect3::sub(this->max(), this->min());
	}
	bool Box3D::containtsPoint(const Vect3& p)
	{
		if (p.x() > this->_min.x() || p.x() < this->_max.x() ||
			p.y() > this->_min.y() || p.y() < this->_max.y() ||
			p.z() > this->_min.z() || p.z() < this->_max.z())
		{
			return true;
		}
		return false;
	}
	bool Box3D::containsBox(const Box3D& b)
	{
		if ((this->_min.x() <= b._min.x()) && (b._max.x() <= this->_max.x()) &&
			(this->_min.y() <= b._min.y()) && (b._max.y() <= this->_max.y()) &&
			(this->_min.z() <= b._min.z()) && (b._max.z() <= this->_max.z()))
		{
			return true;
		}
		return false;
	}
	bool Box3D::intersectsBox(const Box3D& b)
	{
		if (b._max.x() < this->_min.x() || b._min.x() > this->_max.x() ||
			b._max.y() < this->_min.y() || b._min.y() > this->_max.y() ||
			b._max.z() < this->_min.z() || b._min.z() > this->_max.z())
		{
			return false;
		}
		return true;
	}
	bool Box3D::isEqual(const Box3D& b)
	{
		return b.min() == this->_min && b.max() == this->_max;
	}
}
