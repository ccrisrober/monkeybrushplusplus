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

#ifndef __MB_EULER_ANGLE__
#define __MB_EULER_ANGLE__

#include <mb/api.h>

#include <iostream>
#include <functional>

#include "Vect3.hpp"
#include "Mat4.hpp"
#include "Mathf.hpp"

namespace mb
{
    MB_API
	typedef enum
	{
         xyx, zyx, zyz, zxy, zxz, yxz, yxy, yzx, yzy, xyz, xzy, xzx
	} RotSeq;
	class EulerAngle {
	public:
        MB_API
		EulerAngle(float x = 0.0f, float y = 0.0f, float z = 0.0f, RotSeq order = RotSeq::xyz);
        MB_API
		EulerAngle(const Vect3& v, RotSeq order = RotSeq::xyz);
        MB_API
		void setCallback(std::function<void()> f);

        MB_API
        float x() const;
        MB_API
        float y() const;
        MB_API
        float z() const;

        MB_API
        void x(const float& v);
        MB_API
        void y(const float& v);
        MB_API
        void z(const float& v);
        
        MB_API
        void set(const float& vx, const float& vy, const float& vz);
        MB_API
		void reset();
        MB_API
        static EulerAngle createFromVec3(const Vect3& v, RotSeq order = RotSeq::xyz);
        MB_API
		EulerAngle& setFromRotationMatrix(const Mat4& mat);
        MB_API
		EulerAngle& setFromRotationMatrix(const Mat4& mat, RotSeq order, bool update = false);
        MB_API
		EulerAngle& setFromQuaternion(const Quat& q, RotSeq order, bool update = false);
        MB_API
        RotSeq order() const;
        friend std::ostream& operator<<(std::ostream& str, const EulerAngle& v)
        {
            str << "EulerAngle(";
            str << v._values[0] << ", " << v._values[1] << ", " << v._values[2] << ", " << v.orderToString();
            str << ")";
            return str;
        }
	protected:
        const char* orderToString() const;
        std::vector<float> _values;
        RotSeq _order;
		std::function<void()> _onChange;
	};
}

#endif /* __MB_EULER_ANGLE__ */
