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

#ifndef __MB_COLOR4__
#define __MB_COLOR4__

#include <mb/api.h>

#include "../maths/Vect4.hpp"
#include "Color3.hpp"

namespace mb
{
	class Color4
    {
	public:
        MB_API
		Color4(const Color3& color);
        MB_API
		Color4(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

        MB_API
        float r() const;
        MB_API
        float g() const;
        MB_API
        float b() const;
        MB_API
        float a() const;

        MB_API
        void r(const float v);
        MB_API
        void g(const float v);
        MB_API
        void b(const float v);
        MB_API
        void a(const float v);
        
        MB_API
		static Color4 fromColor3(const Color3& color);
        MB_API
		static Color4 lerp(const Color4& minColor, const Color4& maxColor, float alpha);
	protected:
		Vect4 _color;
    };
}

#endif /* __MB_COLOR4__ */
