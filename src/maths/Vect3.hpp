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

#ifndef __MB_VECT3__
#define __MB_VECT3__

#include <vector>

namespace MB {
	class Vect3 {
	public:
		Vect3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
		{
			this->_value.resize(3);
			this->_value[0] = x;
			this->_value[1] = y;
			this->_value[2] = z;
		}
		float x() const {
			return this->_value[0];
		}
		void x(float v) {
			this->_value[0] = v;
		}
		float y() const {
			return this->_value[1];
		}
		void y(float v) {
			this->_value[1] = v;
		}
		float z() const {
			return this->_value[2];
		}
		void z(float v) {
			this->_value[2] = v;
		}
		static Vect3 createFromScalar(float value = 0.0f)
		{
			return Vect3(value, value, value);
		}
		Vect3 add(Vect3 v)
		{
			Vect3 vv(
				this->_value[0] + v._value[0],
				this->_value[1] + v._value[1],
				this->_value[2] + v._value[2]
			);

			return vv;
		}
		Vect3 sub(Vect3 v)
		{
			Vect3 vv(
				this->_value[0] - v._value[0],
				this->_value[1] - v._value[1],
				this->_value[2] - v._value[2]
			);

			return vv;
		}
		Vect3 mult(Vect3 v)
		{
			Vect3 vv(
				this->_value[0] * v._value[0],
				this->_value[1] * v._value[1],
				this->_value[2] * v._value[2]
			);

			return vv;
		}
		Vect3 multByScalar(float s)
		{
			Vect3 vv(
				this->_value[0] * s,
				this->_value[1] * s,
				this->_value[2] * s
			);

			return vv;
		}
		Vect3 div(Vect3 v)
		{
			Vect3 vv(
				this->_value[0] / v._value[0],
				this->_value[1] / v._value[1],
				this->_value[2] / v._value[2]
			);

			return vv;
		}
		static float distance(Vect3& v, Vect3& v2)
		{
			return sqrt(squaredDistance(v, v2));
		}
		static float squaredDistance(Vect3& v, Vect3& v2)
		{
			Vect3 vsub = v2.sub(v);
			return (vsub._value[0] * vsub._value[0] + vsub._value[1] * vsub._value[1] + vsub._value[2] * vsub._value[2]);
		}
	protected:
		std::vector<float> _value;
	};
}

#endif /* __MB_VECT3__ */