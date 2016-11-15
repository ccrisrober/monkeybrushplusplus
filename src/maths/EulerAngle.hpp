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

#ifndef __MB_EULER_ANGLE__
#define __MB_EULER_ANGLE__

#include "Vect3.hpp"
#include "Mat4.hpp"

namespace MB {
	typedef enum
	{
    	zyx, zyz, zxy, zxz, yxz, yxy, yzx, yzy, xyz, xyx, xzy, xzx
	} RotSeq;
	class EulerAngle {
	public:
		EulerAngle(float x = 0.0f, float y = 0.0f, float z = 0.0f, RotSeq order = RotSeq::xyz)
		: _order(order)
		{
			_value.reserve(3);
			set(x, y, z);
		}
		void setCallback(std::function<void()> f)
		{
			this->_onChange = f;
		}
        float x() const {
        	return this->_value[0];
        }
        float y() const {
        	return this->_value[1];
        }
        float z() const {
        	return this->_value[2];
        }
        void x(float v) {
            this->_value[0] = v;
            this->_onChange();
        }
        void y(float v) {
            this->_value[1] = v;
            this->_onChange();
        }
        void z(float v) {
            this->_value[2] = v;
            this->_onChange();
        }
        void set(float vx, float vy, float vz)
        {
        	this->_value[0] = vx;
        	this->_value[1] = vy;
        	this->_value[2] = vz;
            this->_onChange();
        }
        static EulerAngle createFromVec3(const Vect3& v, RotSeq order = RotSeq::xyz)
		{
			return EulerAngle(v.x(), v.y(), v.z(), order);
		}
		/*EulerAngle setFromRotationMatrix(const Mat4& mat, RotSeq order, bool update = false)
		{

		}
		EulerAngle setFromQuaternion(const Quat& q, RotSeq order, bool update = false)
		{
			Mat4 matrix;
			if (!order)
			{
				order = this->_order;
			}
		}*/
	protected:
        std::vector<float> _value;
        RotSeq _order;
		std::function<void()> _onChange;
	};
}

#endif /* __MB_EULER_ANGLE__ */
