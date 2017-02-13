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

#include <mb/api.h>

#include <iostream>
#include <vector>

namespace mb
{
	class Vect2
	{
	public:
		MB_API
		Vect2(float x = 0.0f, float y = 0.0f);
		
		MB_API
		float x() const;
		MB_API
		void x(const float& v);
		MB_API
		float y() const;
		MB_API
		void y(const float& v);
		MB_API
		bool operator!=(const Vect2& v);
		MB_API
		bool operator==(const Vect2& v);
		MB_API
		friend std::ostream& operator<<(std::ostream& str, const Vect2& v);
		Vect2& multByScalar(float s);
		/**
		* Adds two Vect2´s
		* @param  {Vect2}    v  First Vect2 operand
		* @param  {Vect2}    v2 Second Vect2 operand
		* @param  {Vect2 = null} dest Destiny Vect2 (optional)
		* @return {number} a new Vect2
		*/
		static Vect2 add(const Vect2& v, const Vect2& v2);
		/**
		* Subtracts two Vect2´s
		* @param  {Vect2}    v  First Vect2 operand
		* @param  {Vect2}    v2 Second Vect2 operand
		* @param  {Vect2 = null} dest Destiny Vect2 (optional)
		* @return {number} a new Vect2
		*/
		static Vect2 sub(const Vect2& v, const Vect2& v2);
		Vect2& scale(float value);
    public:
        std::vector<float> _values;
	};
}

#endif /* __MB_VECT2__ */
