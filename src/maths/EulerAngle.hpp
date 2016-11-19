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

#include <iostream>
#include <functional>

#include "Vect3.hpp"
#include "Mat4.hpp"
#include "Mathf.hpp"

namespace MB
{
	typedef enum
	{
         xyx, zyx, zyz, zxy, zxz, yxz, yxy, yzx, yzy, xyz, xzy, xzx
	} RotSeq;
	class EulerAngle {
	public:
		EulerAngle(float x = 0.0f, float y = 0.0f, float z = 0.0f, RotSeq order = RotSeq::xyz);
		EulerAngle(const Vect3& v, RotSeq order = RotSeq::xyz);
		void setCallback(std::function<void()> f);
        float x() const;
        float y() const;
        float z() const;
        void x(const float& v);
        void y(const float& v);
        void z(const float& v);
        void set(const float& vx, const float& vy, const float& vz);
		void reset();
        static EulerAngle createFromVec3(const Vect3& v, RotSeq order = RotSeq::xyz);
		EulerAngle& setFromRotationMatrix(const Mat4& mat);
		EulerAngle& setFromRotationMatrix(const Mat4& mat, RotSeq order, bool update = false);
		EulerAngle& setFromQuaternion(const Quat& q, RotSeq order, bool update = false);
        RotSeq order() const;
        friend std::ostream& operator<<(std::ostream& str, const EulerAngle& v) {
            str << "EulerAngle(";
            str << v._values[0] << ", " << v._values[1] << ", " << v._values[2] << ", " << v.orderToString();
            str << ")";
            return str;
        }
	protected:
        inline const char* orderToString() const
        {
            switch (_order)
            {
            case xyx:   return "xyx";
            case zyx:   return "zyx";
            case zyz:   return "zyz";
            case zxy:   return "xyx";
            case zxz:   return "zxz";

            case yxz:   return "yxz";
            case yxy:   return "yxy";
            case yzx:   return "yzx";

            case yzy:   return "yzy";
            case xyz:   return "xyz";
            case xzy:   return "xzy";
            case xzx:   return "xzx";
            }
            throw;
        }
        std::vector<float> _values;
        RotSeq _order;
		std::function<void()> _onChange;
	};
}

#endif /* __MB_EULER_ANGLE__ */
