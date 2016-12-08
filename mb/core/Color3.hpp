/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 * <https://github.com/maldicion069/monkeybrushplusplus>
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

#include <mb/api.h>

#include "../maths/Vect3.hpp"
#include <cmath>

namespace mb
{
  class Color3
    {
  public:
        MB_API
    Color3(float r = 1.0f, float g = 1.0f, float b = 1.0f);
        MB_API
    Color3(const Color3& c);
        MB_API
    Color3& operator=(const Color3& c);
        MB_API
    Color3& copy(const Color3& c);

        MB_API
        float r() const;
        MB_API
        float g() const;
        MB_API
        float b() const;

        MB_API
        void r(const float v);
        MB_API
        void g(const float v);
        MB_API
        void b(const float v);

        MB_API
    static Color3 createFromHSV(float h, float s, float v);
        MB_API
        static Color3 createFromHex(int hex);
        MB_API
    static Color3 lerp(const Color3& minColor, const Color3& maxColor, float alpha);
        /**
         * Convert current color from gamma to linear range.
         * @param  {number = 2.2} gammaFactor Gamma factor value
         * @return {Color3}          New color generated.
         */
        MB_API
    Color3& gammaToLinear(const float& gammaFactor = 2.2f);
        /**
         * Convert current color from linear to gamma range.
         * @param  {number = 2.2}         gammaFactor Gamma factor value
         * @return {Color3}          New color generated.
         */
        MB_API
    Color3& linearToGamma(const float& gammaFactor = 2.2f);

        MB_API
        static Color3 Aqua;
        MB_API
        static Color3 Beige;
        MB_API
        static Color3 Black;
        MB_API
        static Color3 Blue;
        MB_API
        static Color3 Brown;
        MB_API
        static Color3 Cyan;
        MB_API
        static Color3 Gold;
        MB_API
        static Color3 Green;
        MB_API
        static Color3 Indigo;
        MB_API
        static Color3 Lavender;
        MB_API
        static Color3 Orange;
        MB_API
        static Color3 Pink;
        MB_API
        static Color3 Purple;
        MB_API
        static Color3 Red;
        MB_API
        static Color3 Yellow;
        MB_API
        static Color3 White;
    protected:
    Vect3 _color;
    };
}

#endif /* __MB_COLOR3__ */
