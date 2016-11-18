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

#ifndef __MB_RAY__
#define __MB_RAY__

#include "../maths/Vect3.hpp"

namespace MB
{
	class Ray
    {
	public:
		Ray(const Vect3& origin = Vect3::fromScalar(0.0f),
			const Vect3& direction = Vect3::fromScalar(0.0f))
		: _origin(origin)
		, _direction(direction)
		{
		}
		Vect3 origin() const
		{
			return this->_origin;
		}
		Vect3 direction() const
		{
			return this->_direction;
		}
		void origin(const Vect3& ori)
		{
			this->_origin = ori;
		}
		void direction(const Vect3& dir)
		{
			this->_direction = dir;
		}
		Vect3 at(const float t)
		{
			return Vect3(
				this->_origin.x() + t * this->_direction.x(),
				this->_origin.y() + t * this->_direction.y(),
				this->_origin.z() + t * this->_direction.z()
			);
		}
        // public lookAt(v: MB.Vect3) {
        //     this._direction = MB.Vect3.sub(v, this._origin).normalize();
        // };
    protected:
    	Vect3 _origin;
    	Vect3 _direction;
    };
}

#endif /* __MB_RAY__ */
