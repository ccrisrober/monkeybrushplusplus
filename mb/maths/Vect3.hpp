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

#include <mb/api.h>

#include <iostream>
#include <vector>
#include <cmath>

namespace mb
{
	class Color3;
	class Vect3
	{
	public:
		MB_API
		static Vect3 xAxis;
		MB_API
		static Vect3 yAxis;
		MB_API
		static Vect3 zAxis;
		MB_API
		static Vect3 up;
		MB_API
		Vect3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
		MB_API
		Vect3(const Color3& color);
		MB_API
        virtual ~Vect3(void)
        {
        }
		MB_API
		float distanceToSquared(const Vect3& v)
		{
			float
				dx = x() - v.x(),
				dy = y() - v.y(),
				dz = z() - v.z();

			return (dx * dx) + (dy * dy) + (dz * dz);
		}
		MB_API
		float x() const;
		MB_API
		void x(const float& v);
		MB_API
		float y() const;
		MB_API
		void y(const float& v);
		MB_API
		float z() const;
		MB_API
		void z(const float& v);
		MB_API
		static Vect3 createFromScalar(float value = 0.0f);
		// TODO: CONST&??
		MB_API
		void set(float x_, float y_, float z_);
		MB_API
		Vect3 add(const Vect3& v);
		MB_API
		Vect3 sub(const Vect3& v);
		MB_API
		static Vect3 sub(const Vect3& v1, const Vect3& v2);
		MB_API
		Vect3 mult(const Vect3& v);
		MB_API
		Vect3 multByScalar(float s);
		MB_API
		Vect3 div(const Vect3& v);
		MB_API
		static float distance(const Vect3& v, const Vect3& v2);
		MB_API
		static float squaredDistance(const Vect3& v, const Vect3& v2);
		MB_API
		static Vect3 cross(const Vect3& v, const Vect3& v2);
		MB_API
		float length();
		MB_API
		float squaredLength();
		MB_API
		void normalize();
		MB_API
		static Vect3 scaleAndAdd(const Vect3& a, const Vect3& b, const float& scale);
		MB_API
		static Vect3 add(const Vect3& v, const Vect3& v2);
		MB_API
		static float dot(const Vect3& v, const Vect3& v2);
		MB_API
		Vect3& scale(float value);
		MB_API
		virtual bool operator==(const Vect3& other) const;
		MB_API
		bool operator!=(const Vect3& v);
		MB_API
		bool operator==(const Vect3& v);
		MB_API
		friend std::ostream& operator<<(std::ostream& str, const Vect3& v);

		/*MB_API
		Vect3& applyMat4(const Mat4& mat)
		{
			auto x = this->x(),
				y = this->y(),
				z = this->z();

			this->x(mat._values[0] * x + mat._values[4] * y +
				mat._values[8] * z + mat._values[12]);
			this->y(mat._values[1] * x + mat._values[5] * y +
				mat._values[9] * z + mat._values[13]);
			this->z(mat._values[2] * x + mat._values[6] * y +
				mat._values[10] * z + mat._values[14]);

			return *this;
		}*/
	public:
		std::vector<float> _values;
	};
}

#endif /* __MB_VECT3__ */
