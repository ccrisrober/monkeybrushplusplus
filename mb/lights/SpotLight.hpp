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

#ifndef __MB_SPOT_LIGHT__
#define __MB_SPOT_LIGHT__

#include <mb/api.h>

#include "Light.hpp"

namespace mb
{
	class SpotLight: public Light
	{
	public:
		MB_API
		SpotLight(const Vect3 pos = Vect3::createFromScalar(0.0f),
			const Vect3 dir = Vect3::createFromScalar(0.0f), float coff = 1.0f);
		MB_API
		Vect3 position() const;
		MB_API
		Vect3 direction() const;
		MB_API
		float cutOff() const;
		MB_API
		void position(const Vect3 pos);
		MB_API
		void direction(const Vect3 dir);
		MB_API
		void cutOff(const float coff);
	protected:
		Vect3 _position;
		Vect3 _direction;
		float _cutOff;
    };
}

#endif /* __MB_SPOT_LIGHT__ */
