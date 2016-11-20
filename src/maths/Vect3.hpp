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
	class Color3;
	class Vect3
	{
	public:
		static Vect3 xAxis;
		static Vect3 yAxis;
		static Vect3 zAxis;
		static Vect3 up;
		Vect3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
		Vect3(const Color3& color);
        virtual ~Vect3(void)
        {
        }
		float x() const;
		void x(const float& v);
		float y() const;
		void y(const float& v);
		float z() const;
		void z(const float& v);
		static Vect3 createFromScalar(float value = 0.0f);
		// TODO: CONST&??
		void set(float x_, float y_, float z_);
		Vect3 add(const Vect3& v);
		Vect3 sub(const Vect3& v);
		static Vect3 sub(const Vect3& v1, const Vect3& v2);
		Vect3 mult(const Vect3& v);
		Vect3 multByScalar(float s);
		Vect3 div(const Vect3& v);
		static float distance(const Vect3& v, const Vect3& v2);
		static float squaredDistance(const Vect3& v, const Vect3& v2);
		static Vect3 cross(const Vect3& v, const Vect3& v2);
		float length();
		float squaredLength();
		void normalize();
		static Vect3 scaleAndAdd(const Vect3& a, const Vect3& b, const float& scale);
		static Vect3 add(const Vect3& v, const Vect3& v2);
		static float dot(const Vect3& v, const Vect3& v2);
		virtual bool operator==(const Vect3& other) const;
		bool operator!=(const Vect3& v);
		bool operator==(const Vect3& v);
        friend std::ostream& operator<<(std::ostream& str, const Vect3& v)
        {
            str << "Vect3(";
            str << v._values[0] << ", " << v._values[1] << ", " << v._values[2];
			str << ")";
            return str;
        }
	public:
		std::vector<float> _values;
	};
}

#endif /* __MB_VECT3__ */
