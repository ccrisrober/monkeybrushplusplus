/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal
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

#ifndef __MB_COLOR3__
#define __MB_COLOR3__

#include "../maths/Vect3.hpp"

namespace MB
{
	class Color3
    {
	public:
		Color3(float r = 1.0f, float g = 1.0f, float b = 1.0f);
        float r() const;
        float g() const;
        float b() const;
        void r(const float v);
        void g(const float v);
        void b(const float v);

        static Color3 createFromHex(int hex);

        static Color3 Aqua;
        static Color3 Beige;
        static Color3 Black;
        static Color3 Blue;
        static Color3 Brown;
        static Color3 Cyan;
        static Color3 Gold;
        static Color3 Green;
        static Color3 Indigo;
        static Color3 Lavender;
        static Color3 Orange;
        static Color3 Pink;
        static Color3 Purple;
        static Color3 Red;
        static Color3 Yellow;
        static Color3 White;

	protected:
		Vect3 _color;
    };
}

#endif /* __MB_COLOR3__ */
