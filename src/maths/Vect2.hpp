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

#ifndef __MB_VECT2__
#define __MB_VECT2__

#include <iostream>
#include <vector>

namespace MB
{
	class Vect2
	{
	public:
		Vect2(float x = 0.0f, float y = 0.0f);
		float x() const;
		void x(const float& v);
		float y() const;
		void y(const float& v);
		bool operator!=(const Vect2& v);
		bool operator==(const Vect2& v);
        friend std::ostream& operator<<(std::ostream& str, const Vect2& v) {
            str << "Vect2(";
            str << v._values[0] << ", " << v._values[1];
            str << ")";
            return str;
        }

		Vect2& multByScalar(float s)
		{
			x(x() * s);
			y(y() * s);

			return *this;
		}
		/**
		* Adds two Vect2´s
		* @param  {Vect2}    v  First Vect2 operand
		* @param  {Vect2}    v2 Second Vect2 operand
		* @param  {Vect2 = null} dest Destiny Vect2 (optional)
		* @return {number} a new Vect2
		*/
		static Vect2 add(const Vect2& v, const Vect2& v2)
		{
			return Vect2(
				v.x() + v2.x(),
				v.y() + v2.y()
			);
		}
		/**
		* Subtracts two Vect2´s
		* @param  {Vect2}    v  First Vect2 operand
		* @param  {Vect2}    v2 Second Vect2 operand
		* @param  {Vect2 = null} dest Destiny Vect2 (optional)
		* @return {number} a new Vect2
		*/
		static Vect2 sub(const Vect2& v, const Vect2& v2)
		{
			return Vect2(
				v.x() - v2.x(),
				v.y() - v2.y()
			);
		}
		Vect2& scale(float value)
		{
			this->x(x() * value);
			this->y(y() * value);

			return *this;
		}
    public:
        std::vector<float> _values;
	};
}

#endif /* __MB_VECT2__ */
