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

#ifndef __MB_LIGHT__
#define __MB_LIGHT__

#include <mb/api.h>

#include "../core/Color3.hpp"

namespace MB
{
	class Light
	{
	public:
		MB_API
		float intensity() const;
		MB_API
		Vect3 attenuation() const;
		MB_API
        bool isEnable() const;
		MB_API
        Color3 color() const;
		MB_API
        Color3 specColor() const;
		MB_API
        void intensity(const float i);
		MB_API
        void attenuation(const Vect3 att);
		MB_API
        void enabled(const bool e);
		MB_API
        void color(const Color3& c);
		MB_API
        void specColor(const Color3& sc);
	protected:
		Light();
		float _intensity;
		bool _enable;
		Vect3 _attenuation;
        Color3 _color;
        Color3 _specColor;
	};
}

#endif /* __MB_LIGHT__ */
