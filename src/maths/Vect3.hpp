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

#ifndef __MB_VECT3__
#define __MB_VECT3__

#include <iostream>
#include <vector>
#include <cmath>

namespace MB
{
	class Vect3
	{
	public:
		static Vect3 xAxis;
		static Vect3 yAxis;
		static Vect3 zAxis;
		static Vect3 up;
		Vect3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
		{
			this->_values.resize(3);
			this->_values[0] = x;
			this->_values[1] = y;
			this->_values[2] = z;
		}
        virtual ~Vect3(void)
        {
        }
		float x() const
		{
			return this->_values[0];
		}
		void x(const float& v)
		{
			this->_values[0] = v;
		}
		float y() const
		{
			return this->_values[1];
		}
		void y(const float& v)
		{
			this->_values[1] = v;
		}
		float z() const
		{
			return this->_values[2];
		}
		void z(const float& v)
		{
			this->_values[2] = v;
		}
		static Vect3 createFromScalar(float value = 0.0f)
		{
			return Vect3(value, value, value);
		}
		// TODO: CONST&??
		void set(float x_, float y_, float z_)
		{
			x(x_);
			y(y_);
			z(z_);
		}
		Vect3 add(const Vect3& v)
		{
			Vect3 vv(
				this->_values[0] + v._values[0],
				this->_values[1] + v._values[1],
				this->_values[2] + v._values[2]
			);

			return vv;
		}
		Vect3 sub(const Vect3& v)
		{
			Vect3 vv(
				this->_values[0] - v._values[0],
				this->_values[1] - v._values[1],
				this->_values[2] - v._values[2]
			);

			return vv;
		}
		static Vect3 sub(const Vect3& v1, const Vect3& v2)
		{
			Vect3 vv(
				v1._values[0] - v2._values[0],
				v1._values[1] - v2._values[1],
				v1._values[2] - v2._values[2]
			);

			return vv;
		}
		Vect3 mult(const Vect3& v)
		{
			Vect3 vv(
				this->_values[0] * v._values[0],
				this->_values[1] * v._values[1],
				this->_values[2] * v._values[2]
			);

			return vv;
		}
		Vect3 multByScalar(float s)
		{
			Vect3 vv(
				this->_values[0] * s,
				this->_values[1] * s,
				this->_values[2] * s
			);

			return vv;
		}
		Vect3 div(const Vect3& v)
		{
			Vect3 vv(
				this->_values[0] / v._values[0],
				this->_values[1] / v._values[1],
				this->_values[2] / v._values[2]
			);

			return vv;
		}
		static float distance(const Vect3& v, const Vect3& v2)
		{
            return std::sqrt(squaredDistance(v, v2));
		}
		static float squaredDistance(const Vect3& v, const Vect3& v2)
		{
			Vect3 vsub = Vect3::sub(v2, v);;
            return (vsub._values[0] * vsub._values[0] + vsub._values[1] * vsub._values[1] +
                    vsub._values[2] * vsub._values[2]);
		}
		static Vect3 cross(const Vect3& v, const Vect3& v2)
		{
			float
				x = v.x(),
				y = v.y(),
				z = v.z();

			float
				x2 = v2.x(),
				y2 = v2.y(),
				z2 = v2.z();
			
			return Vect3(
				y * z2 - z * y2,
				z * x2 - x * z2,
				x * y2 - y * x2
			);
		}
		float length()
		{
			return std::sqrt(squaredLength());
		}
		float squaredLength()
		{
			float 
				x = this->x(),
				y = this->y(),
				z = this->z();

			return (x * x + y * y + z * z);
		}
		void normalize()
		{
			float l = length();

			if (l == 1.0f) {
				return;
			}

			if (l == 0) {
				x(0.0f);
				y(0.0f);
				z(0.0f);

				return;
			}

			l = 1.0f / l;

			x(x() * l);
			y(y() * l);
			z(z() * l);
		}
		static Vect3 scaleAndAdd(const Vect3& a, const Vect3& b, const float& scale)
		{
			return Vect3(
				a.x() + (b.x() * scale),
				a.y() + (b.y() * scale),
				a.z() + (b.z() * scale)
			);
		}
		static Vect3 add(const Vect3& v, const Vect3& v2)
		{
			return Vect3(
				v.x() + v2.x(),
				v.y() + v2.y(),
				v.z() + v2.z()
			);
		}
		static float dot(const Vect3& v, const Vect3& v2)
		{
			float
				x = v.x(),
				y = v.y(),
				z = v.z();

			float
				x2 = v2.x(),
				y2 = v2.y(),
				z2 = v2.z();

			return (x * x2 + y * y2 + z * z2);
		}
		virtual bool operator==(const Vect3& other) const
		{
			for (unsigned int i = 0; i < 3; ++i) {

				if (std::abs(this->_values[i] - other._values[i]) != 0.0f) {
					return false;
				}
			}
			return true;
        }
        friend std::ostream& operator<<(std::ostream& str, const Vect3& v) {
            str << std::string("Vect3(");
            str << v._values[0] << std::string(", ") << v._values[1] << std::string(", ") << v._values[2];
            str << std::string(")");
            return str;
        }
	public:
		std::vector<float> _values;
	};
}

#endif /* __MB_VECT3__ */
