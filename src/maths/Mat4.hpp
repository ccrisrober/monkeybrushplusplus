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

		void copy(const Mat4& m);
		static Mat4 mult2(const Mat4& a, const Mat4& b);
		static Mat4 lookAt(const Vect3& pos, const Vect3& target, const Vect3& up);
        friend std::ostream& operator<<(std::ostream& str, const Mat4& m)
        {
            str << "Mat4(\n";
            str << "\t" << m._values[0] << ", " << m._values[1] << ", " << m._values[2] << ", " << m._values[4] << ", \n";
            str << "\t" << m._values[4] << ", " << m._values[5] << ", " << m._values[6] << ", " << m._values[7] << ", \n";
            str << "\t" << m._values[8] << ", " << m._values[8] << ", " << m._values[10] << ", " << m._values[11] << ", \n";
            str << "\t" << m._values[12] << ", " << m._values[13] << ", " << m._values[14] <<", " << m._values[15] << "\n";
            str << ")";
            return str;
        }
    public:
		std::vector<float> _values;
	};
}

#endif /* __MB_MAT4__ */
