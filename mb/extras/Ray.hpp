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

#include <mb/api.h>

#include "../maths/Vect3.hpp"

namespace MB
{
	class Ray
    {
	public:
		MB_API
		Ray(const Vect3& origin = Vect3::createFromScalar(0.0f),
			const Vect3& direction = Vect3::createFromScalar(0.0f));
		MB_API
		Vect3 origin() const;
		MB_API
		Vect3 direction() const;
		MB_API
		void origin(const Vect3& ori);
		MB_API
		void direction(const Vect3& dir);
		MB_API
		Vect3 at(const float t);
        // public lookAt(v: MB.Vect3) {
        //     this._direction = MB.Vect3.sub(v, this._origin).normalize();
        // };
    protected:
    	Vect3 _origin;
    	Vect3 _direction;
    };
}

#endif /* __MB_RAY__ */
