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

#ifndef __MB_QUAT__
#define __MB_QUAT__

#include <mb/api.h>

#include <vector>
#include <functional>
#include <cmath>
#include "EulerAngle.hpp"
#include "Mat4.hpp"

namespace mb
{
	class Quat
	{
	public:
		MB_API
		Quat(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
		MB_API
        Quat(const Quat& q);
		MB_API
        virtual ~Quat(void)
        {
        }
		MB_API
        Quat& operator=(const Quat& q);
		MB_API
        Quat& copy(const Quat& q);
		MB_API
		void setCallback(std::function<void()> f);

		MB_API
		float x() const;
		MB_API
		float y() const;
		MB_API
		float z() const;
		MB_API
		float w() const;

		MB_API
		void x(const float& v);
		MB_API
		void y(const float& v);
		MB_API
		void z(const float& v);
		MB_API
		void w(const float& v);
		
		MB_API
		float pitch();
		MB_API
		float yaw();
		MB_API
		float roll();
		MB_API
		static float dot(const Quat& q1, const Quat& q2);
		MB_API
		void reset();
		MB_API
		Quat& inverse();
		MB_API
		Quat& conjugate();
		MB_API
		Quat& setFromAxisAngle(const Vect3& axis, float angle);
		MB_API
        Quat& setFromRotationMatrix(const Mat4& mat);
		MB_API
		Quat& add(const Quat& q);
		MB_API
		Quat& rem(const Quat& q);
		MB_API
		Quat& mult(const Quat& q);
		MB_API
		virtual bool operator==(const Quat& other) const;
		MB_API
        Quat& setFromEuler(const EulerAngle& euler);
	protected:
		std::vector<float> _values;
		std::function<void()> _onChange;
	};
}

#endif /* __MB_QUAT__ */
