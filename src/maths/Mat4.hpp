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
    public:
		std::vector<float> _values;
	};
}

#endif /* __MB_MAT4__ */
