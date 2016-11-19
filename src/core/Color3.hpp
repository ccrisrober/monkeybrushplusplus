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

#ifndef __MB_COLOR3__
#define __MB_COLOR3__

#include "../maths/Vect3.hpp"
#include <cmath>

namespace MB
{
	class Color3
    {
	public:
		Color3(float r = 1.0f, float g = 1.0f, float b = 1.0f);

        Color3(const Color3& c)
        {
            this->_color = c._color;
        }
        Color3& operator=(const Color3& c)
        {
            return copy(c);
        }
        Color3& copy( const Color3& c ) {
            r(c.r());
            g(c.g());
            b(c.b());
            return *this;
        }

        float r() const;
        float g() const;
        float b() const;
        void r(const float v);
        void g(const float v);
        void b(const float v);

        static Color3 createFromHSV(float h, float s, float v)
        {
            float r, g, b;
            if ( v == 0.0f ) {
                r = g = b = 0.0;
            } else {
                int i = (int) std::floor (h * 6.0f);
                float f = (h * 6.0f) - i;
                float p = v * (1.0f - s);
                float q = v * (1.0f - (s * f));
                float t = v * (1.0f - (s * (1.0f - f)));

                switch ( i ) {
                    case 0:
                        r = v;
                        g = t;
                        b = p;
                        break;
                    case 1:
                        r = q;
                        g = v;
                        b = p;
                        break;
                    case 2:
                        r = p;
                        g = v;
                        b = t;
                        break;
                    case 3:
                        r = p;
                        g = q;
                        b = v;
                        break;
                    case 4:
                        r = t;
                        g = p;
                        b = v;
                        break;
                    case 5:
                    default:
                        r = v;
                        g = p;
                        b = q;
                        break;
                    }
            }
            return Color3(r, g, b);
        }

        static Color3 createFromHex(int hex);

        static Color3 lerp(const Color3& minColor, const Color3& maxColor, float alpha)
        {

            float r = minColor.r() + (maxColor.r() - minColor.r()) * alpha;
            float g = minColor.g() + (maxColor.g() - minColor.g()) * alpha;
            float b = minColor.b() + (maxColor.b() - minColor.b()) * alpha;

            return Color3(r, g, b);
        }
        /**
         * Convert current color from gamma to linear range.
         * @param  {number = 2.2} gammaFactor Gamma factor value
         * @return {Color3}          New color generated.
         */
        Color3& gammaToLinear(const float& gammaFactor = 2.2f)
        {
            this->r(std::pow(this->r(), gammaFactor));
            this->g(std::pow(this->g(), gammaFactor));
            this->b(std::pow(this->b(), gammaFactor));

            return *this;
        }
        /**
         * Convert current color from linear to gamma range.
         * @param  {number = 2.2}         gammaFactor Gamma factor value
         * @return {Color3}          New color generated.
         */
        Color3& linearToGamma(const float& gammaFactor = 2.2f)
        {
            float invGamma = (gammaFactor > 0.0f) ? (1.0f / gammaFactor) : 1.0f;

            this->r(std::pow(this->r(), invGamma));
            this->g(std::pow(this->g(), invGamma));
            this->b(std::pow(this->b(), invGamma));

            return *this;
        }

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
