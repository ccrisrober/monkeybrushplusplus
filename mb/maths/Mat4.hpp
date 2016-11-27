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

#ifndef __MB_MAT4__
#define __MB_MAT4__

#include <mb/api.h>

#include <vector>
#include <iostream>
#include "Vect3.hpp"

namespace MB
{
	class Quat;
	class Mat4
	{
	public:
		MB_API
		Mat4();
		MB_API
		Mat4(const std::vector<float> values);
		MB_API
		float determinant() const;
		MB_API
		void compose(Vect3& position, Quat& quaternion, Vect3& scale);
		MB_API
		void decompose(Vect3& /*position*/, Quat& /*quaternion*/, Vect3& /*scale*/);
		MB_API
		void set(
			float e11, float e12, float e13, float e14,
			float e21, float e22, float e23, float e24,
			float e31, float e32, float e33, float e34,
			float e41, float e42, float e43, float e44);
		MB_API
		static Mat4 perspective(const float& fovy, const float& aspect, 
			const float& near, const float& far);
		MB_API
		static Mat4 orthographic(const float& left, const float& right, const float& bottom, 
			const float& top, const float& near, const float& far);

		MB_API
		void copy(const Mat4& m);
		MB_API
		static Mat4 mult2(const Mat4& a, const Mat4& b);
		MB_API
		static Mat4 lookAt(const Vect3& pos, const Vect3& target, const Vect3& up);
		
		MB_API
		friend std::ostream& operator<<(std::ostream& str, const Mat4& m);
    public:
		std::vector<float> _values;
	};
}

#endif /* __MB_MAT4__ */
