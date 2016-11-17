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

#include <vector>
#include <functional>
#include <cmath>
#include "EulerAngle.hpp"
#include "Mat4.hpp"

namespace MB
{
	class Quat
	{
	public:
		Quat(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
        Quat(const Quat& q);
        virtual ~Quat(void)
        {
        }
        Quat& operator=(const Quat& q);
        Quat& copy(const Quat& q);
		void setCallback(std::function<void()> f);
		float x() const;
		float y() const;
		float z() const;
		float w() const;
		void x(const float& v);
		void y(const float& v);
		void z(const float& v);
		void w(const float& v);
		float pitch();
		float yaw();
		float roll();
		static float dot(const Quat& q1, const Quat& q2);
		void reset();
		Quat& inverse();
		Quat& conjugate();
		Quat& setFromAxisAngle(const Vect3& axis, float angle);
        Quat& setFromRotationMatrix(const Mat4& mat);
		Quat& add(const Quat& q);
		Quat& rem(const Quat& q);
		Quat& mult(const Quat& q);
		virtual bool operator==(const Quat& other) const;
        Quat& setFromEuler(const EulerAngle& euler);
	protected:
		std::vector<float> _values;
		std::function<void()> _onChange;
	};
}

#endif /* __MB_QUAT__ */
