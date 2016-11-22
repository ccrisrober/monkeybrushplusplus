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
#include "Ray.hpp"

namespace MB
{
	Ray::Ray(const Vect3& origin, const Vect3& direction)
	: _origin(origin)
	, _direction(direction)
	{
	}
	Vect3 Ray::origin() const
	{
		return this->_origin;
	}
	Vect3 Ray::direction() const
	{
		return this->_direction;
	}
	void Ray::origin(const Vect3& ori)
	{
		this->_origin = ori;
	}
	void Ray::direction(const Vect3& dir)
	{
		this->_direction = dir;
	}
	Vect3 Ray::at(const float t)
	{
		return Vect3(
			this->_origin.x() + t * this->_direction.x(),
			this->_origin.y() + t * this->_direction.y(),
			this->_origin.z() + t * this->_direction.z()
		);
	}
}
