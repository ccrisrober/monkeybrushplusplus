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

#ifndef __MB_MAT4__
#define __MB_MAT4__

#include "Vect3.hpp"

namespace MB
{
    class Quat;
	class Mat4
	{
	public:
		Mat4()
		{
			static const float _ident[] = {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
			};
			this->_values = std::vector<float>(_ident, _ident + sizeof(_ident) / sizeof(float));
		}

		float determinant() const
		{
			float
				a00 = this->_values[0], a01 = this->_values[1], a02 = this->_values[2], a03 = this->_values[3],
				a10 = this->_values[4], a11 = this->_values[5], a12 = this->_values[6], a13 = this->_values[7],
				a20 = this->_values[8], a21 = this->_values[9], a22 = this->_values[10], a23 = this->_values[11],
				a30 = this->_values[12], a31 = this->_values[13], a32 = this->_values[14], a33 = this->_values[15];

			float
				det00 = a00 * a11 - a01 * a10,
				det01 = a00 * a12 - a02 * a10,
				det02 = a00 * a13 - a03 * a10,
				det03 = a01 * a12 - a02 * a11,
				det04 = a01 * a13 - a03 * a11,
				det05 = a02 * a13 - a03 * a12,
				det06 = a20 * a31 - a21 * a30,
				det07 = a20 * a32 - a22 * a30,
				det08 = a20 * a33 - a23 * a30,
				det09 = a21 * a32 - a22 * a31,
				det10 = a21 * a33 - a23 * a31,
				det11 = a22 * a33 - a23 * a32;

			// Calculate the determinant
			return (det00 * det11 - det01 * det10 + det02 * det09 + det03 * det08 - det04 * det07 + det05 * det06);
		};
		Mat4(const std::vector<float> values)
		{
			this->_values = values;
		}
		void compose(Vect3& /*position*/, Quat& /*quaternion*/, Vect3& /*scale*/)
		{

		}
		void decompose(Vect3& /*position*/, Quat& /*quaternion*/, Vect3& /*scale*/)
		{

		}
		void set(
			float e11, float e12, float e13, float e14,
			float e21, float e22, float e23, float e24,
			float e31, float e32, float e33, float e34,
			float e41, float e42, float e43, float e44)
		{
			this->_values[0] = e11; this->_values[4] = e12; this->_values[8] = e13; this->_values[12] = e14;
			this->_values[1] = e21; this->_values[5] = e22; this->_values[9] = e23; this->_values[13] = e24;
			this->_values[2] = e31; this->_values[6] = e32; this->_values[10] = e33; this->_values[14] = e34;
			this->_values[3] = e41; this->_values[7] = e42; this->_values[11] = e43; this->_values[15] = e44;
        }
    public:
		std::vector<float> _values;
	};
}

#endif /* __MB_MAT4__ */
