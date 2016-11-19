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

#include "../maths/Vect4.hpp"
#include "Color3.hpp"

namespace MB
{
	class Color4
    {
	public:
		Color4(const Color3& color)
		: Color4(color.r(), color.g(), color.b())
		{

		}
		Color4(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
        float r() const;
        float g() const;
        float b() const;
        float a() const;
        void r(const float v);
        void g(const float v);
        void b(const float v);
        void a(const float v);

		static Color4 fromColor3(const Color3& color)
		{
			return Color4(color);
		}
		static Color4 lerp(const Color4& minColor, const Color4& maxColor, float alpha)
		{

			float r = minColor.r() + (maxColor.r() - minColor.r()) * alpha;
			float g = minColor.g() + (maxColor.g() - minColor.g()) * alpha;
			float b = minColor.b() + (maxColor.b() - minColor.b()) * alpha;
			float a = minColor.a() + (maxColor.a() - minColor.a()) * alpha;

			return Color4(r, g, b, a);
		}
	protected:
		Vect4 _color;
    };
}

#endif /* __MB_COLOR4__ */
