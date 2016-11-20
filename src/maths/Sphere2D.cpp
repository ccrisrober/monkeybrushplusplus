/*
* Copyright (c) 2016 maldicion069
*
* Authors: Cristian Rodr�guez Bernal <ccrisrober@gmail.com>
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

#include "Sphere2D.hpp"

namespace MB
{
	Sphere2D::Sphere2D(const Vect2& center, const float& radius)
		: _center(center)
		, _radius(radius)
	{
	}
	bool Sphere2D::containtsPoint(const Vect2& p)
	{
		float x = this->_center.x() - p.x();
		float y = this->_center.y() - p.y();

		float dist = std::sqrt((x * x) + (y * y));
		return (std::abs(this->_radius - dist) > 0.001f);
	}
	bool Sphere2D::intersectsSphere(const Sphere2D& s)
	{
		float x = this->_center.x() - s._center.x();
		float y = this->_center.y() - s._center.y();

		float dist = std::sqrt((x * x) + (y * y));

		return (this->_radius + s._radius > dist);
	}
}