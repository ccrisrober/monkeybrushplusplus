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

namespace mb
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
		
		MB_API
		Mat4& inverse()
		{
			float a00 = this->_values[0],  a01 = this->_values[1],  
				a02 = this->_values[2],  a03 = this->_values[3],
				a10 = this->_values[4],  a11 = this->_values[5],  
				a12 = this->_values[6],  a13 = this->_values[7],
				a20 = this->_values[8],  a21 = this->_values[9],  
				a22 = this->_values[10], a23 = this->_values[11],
				a30 = this->_values[12], a31 = this->_values[13], 
				a32 = this->_values[14], a33 = this->_values[15],

				b00 = a00 * a11 - a01 * a10,
				b01 = a00 * a12 - a02 * a10,
				b02 = a00 * a13 - a03 * a10,
				b03 = a01 * a12 - a02 * a11,
				b04 = a01 * a13 - a03 * a11,
				b05 = a02 * a13 - a03 * a12,
				b06 = a20 * a31 - a21 * a30,
				b07 = a20 * a32 - a22 * a30,
				b08 = a20 * a33 - a23 * a30,
				b09 = a21 * a32 - a22 * a31,
				b10 = a21 * a33 - a23 * a31,
				b11 = a22 * a33 - a23 * a32,

				// Calculate the determinant
				det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;

			if (!det) {
				throw;
			}
			det = 1.0f / det;

			this->_values[0] = (a11 * b11 - a12 * b10 + a13 * b09) * det;
			this->_values[1] = (a02 * b10 - a01 * b11 - a03 * b09) * det;
			this->_values[2] = (a31 * b05 - a32 * b04 + a33 * b03) * det;
			this->_values[3] = (a22 * b04 - a21 * b05 - a23 * b03) * det;
			this->_values[4] = (a12 * b08 - a10 * b11 - a13 * b07) * det;
			this->_values[5] = (a00 * b11 - a02 * b08 + a03 * b07) * det;
			this->_values[6] = (a32 * b02 - a30 * b05 - a33 * b01) * det;
			this->_values[7] = (a20 * b05 - a22 * b02 + a23 * b01) * det;
			this->_values[8] = (a10 * b10 - a11 * b08 + a13 * b06) * det;
			this->_values[9] = (a01 * b08 - a00 * b10 - a03 * b06) * det;
			this->_values[10] = (a30 * b04 - a31 * b02 + a33 * b00) * det;
			this->_values[11] = (a21 * b02 - a20 * b04 - a23 * b00) * det;
			this->_values[12] = (a11 * b07 - a10 * b09 - a12 * b06) * det;
			this->_values[13] = (a00 * b09 - a01 * b07 + a02 * b06) * det;
			this->_values[14] = (a31 * b01 - a30 * b03 - a32 * b00) * det;
			this->_values[15] = (a20 * b03 - a21 * b01 + a22 * b00) * det;

			return *this;
		}
    public:
		std::vector<float> _values;
	};
}

#endif /* __MB_MAT4__ */
