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

#include <vector>
#include <iostream>
#include "Vect3.hpp"

namespace MB
{
	class Quat;
	class Mat4
	{
	public:
		Mat4();
		Mat4(const std::vector<float> values);
		float determinant() const;
		void compose(Vect3& position, Quat& quaternion, Vect3& scale);
		void decompose(Vect3& /*position*/, Quat& /*quaternion*/, Vect3& /*scale*/);
		void set(
			float e11, float e12, float e13, float e14,
			float e21, float e22, float e23, float e24,
			float e31, float e32, float e33, float e34,
			float e41, float e42, float e43, float e44);
		static Mat4 perspective(const float& fovy, const float& aspect, 
			const float& near, const float& far);
		static Mat4 orthographic(const float& left, const float& right, const float& bottom, 
			const float& top, const float& near, const float& far);

		void copy(const Mat4& m)
		{
			this->_values = m._values;
		}
		static Mat4 mult2(const Mat4& a, const Mat4& b)
		{
			std::vector<float> ae = a._values;
			std::vector<float> be = b._values;
			std::vector<float> te(16);

			float a11 = ae[0], a12 = ae[4], a13 = ae[8], a14 = ae[12];
			float a21 = ae[1], a22 = ae[5], a23 = ae[9], a24 = ae[13];
			float a31 = ae[2], a32 = ae[6], a33 = ae[10], a34 = ae[14];
			float a41 = ae[3], a42 = ae[7], a43 = ae[11], a44 = ae[15];

			float b11 = be[0], b12 = be[4], b13 = be[8], b14 = be[12];
			float b21 = be[1], b22 = be[5], b23 = be[9], b24 = be[13];
			float b31 = be[2], b32 = be[6], b33 = be[10], b34 = be[14];
			float b41 = be[3], b42 = be[7], b43 = be[11], b44 = be[15];

			te[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
			te[4] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
			te[8] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
			te[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

			te[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
			te[5] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
			te[9] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
			te[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

			te[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
			te[6] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
			te[10] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
			te[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

			te[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
			te[7] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
			te[11] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
			te[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

			return Mat4(te);
		}
		static Mat4 lookAt(const Vect3& pos, const Vect3& target, const Vect3& up)
		{
			/*if (pos.isEquals(target)) {
				return this.identity;
			}*/

			Vect3 z = Vect3::sub(pos, target);
			z.normalize();

			Vect3 x = Vect3::cross(up, z);
			x.normalize();
			Vect3 y = Vect3::cross(z, x);
			y.normalize();

			std::vector<float> out = {
					x.x(),                y.x(),                z.x(),     0.0f,
					x.y(),                y.y(),                z.y(),     0.0f,
					x.z(),                y.z(),                z.z(),     0.0f,
					-Vect3::dot(x, pos), -Vect3::dot(y, pos), -Vect3::dot(z, pos),     1.0f
			};
			return Mat4(out);
        }
        friend std::ostream& operator<<(std::ostream& str, const Mat4& m) {
            str << std::string("Mat4(\n");
            str << std::string("\t") << m._values[0] << std::string(", ") << m._values[1] << std::string(", ") << m._values[2] << std::string(", ") << m._values[4] << std::string(", \n");
            str << std::string("\t") << m._values[4] << std::string(", ") << m._values[5] << std::string(", ") << m._values[6] << std::string(", ") << m._values[7] << std::string(", \n");
            str << std::string("\t") << m._values[8] << std::string(", ") << m._values[8] << std::string(", ") << m._values[10] << std::string(", ") << m._values[11] << std::string(", \n");
            str << std::string("\t") << m._values[12] << std::string(", ") << m._values[13] << std::string(", ") << m._values[14] <<std::string(", ") << m._values[15] << std::string("\n");
            str << std::string(")");
            return str;
        }
    public:
		std::vector<float> _values;
	};
}

#endif /* __MB_MAT4__ */
