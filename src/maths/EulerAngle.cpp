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

#include "EulerAngle.hpp"
#include "Quat.hpp"

namespace MB
{
	EulerAngle::EulerAngle(float x, float y, float z, RotSeq order)
	: _order(order)
	{
		_values.resize(3);
		set(x, y, z);
	}
	EulerAngle::EulerAngle(const Vect3& v, RotSeq order)
		: EulerAngle(v.x(), v.y(), v.z(), order)
	{
	}
	void EulerAngle::setCallback(std::function<void()> f)
	{
		this->_onChange = f;
	}
    float EulerAngle::x() const
    {
    	return this->_values[0];
    }
    float EulerAngle::y() const
    {
    	return this->_values[1];
    }
    float EulerAngle::z() const
    {
    	return this->_values[2];
    }
    void EulerAngle::x(const float& v)
    {
        this->_values[0] = v;
		if (this->_onChange)	this->_onChange();
    }
    void EulerAngle::y(const float& v)
    {
        this->_values[1] = v;
		if (this->_onChange)	this->_onChange();
    }
    void EulerAngle::z(const float& v)
    {
        this->_values[2] = v;
		if (this->_onChange)	this->_onChange();
    }
    void EulerAngle::set(const float& vx, const float& vy, const float& vz)
    {
    	this->_values[0] = vx;
    	this->_values[1] = vy;
    	this->_values[2] = vz;
		if(_onChange)
			_onChange();
    }
	void EulerAngle::reset()
	{
		this->_values[0] = 0.0f;
		this->_values[1] = 0.0f;
		this->_values[2] = 0.0f;

		if (_onChange)	_onChange();
	}
    EulerAngle EulerAngle::createFromVec3(const Vect3& v, RotSeq order)
	{
		return EulerAngle(v, order);
	}
	EulerAngle& EulerAngle::setFromRotationMatrix(const Mat4& mat)
	{
		return setFromRotationMatrix(mat, this->_order);
	}
	EulerAngle& EulerAngle::setFromRotationMatrix(const Mat4& mat, RotSeq order, 
		bool update)
	{
		this->_order = order;

		float
			m11 = mat._values[0],
			m12 = mat._values[4],
			m13 = mat._values[8];
		float
			m21 = mat._values[1],
			m22 = mat._values[5],
			m23 = mat._values[9];
		float
			m31 = mat._values[2],
			m32 = mat._values[6],
			m33 = mat._values[10];

		if (order == xyz)
		{
			this->y(std::asin(Mathf::clamp(m13, -1.0f, 1.0f)));
			if (std::abs(m13) < 0.99999f)
			{
				this->x(std::atan2(-m23, m33));
				this->z(std::atan2(-m12, m11));
			}
			else
			{
				this->x(std::atan2(m32, m22));
				this->z(0.0f);
			}
		}
		else if (order == yxz)
		{
			this->x(std::asin(-Mathf::clamp(m23, -1.0f, 1.0f)));
			if (std::abs(m23) < 0.99999f)
			{
				this->y(std::atan2(m13, m33));
				this->z(std::atan2(m21, m22));
			}
			else {
				this->y(std::atan2(-m31, m11));
				this->z(0.0f);
			}
		}
		else if (order == zxy)
		{
			this->x(std::asin(Mathf::clamp(m32, -1.0f, 1.0f)));
			if (std::abs(m32) < 0.99999f)
			{
				this->y(std::atan2(-m31, m33));
				this->z(std::atan2(-m12, m22));

			}
			else
			{
				this->y(0.0f);
				this->z(std::atan2(m21, m11));
			}
		}
		else if (order == zyx)
		{
			this->y(std::asin(-Mathf::clamp(m31, -1.0f, 1.0f)));
			if (std::abs(m31) < 0.99999f)
			{
				this->x(std::atan2(m32, m33));
				this->z(std::atan2(m21, m11));
			}
			else
			{
				this->x(0.0f);
				this->z(std::atan2(-m12, m22));
			}
		}
		else if (order == yzx)
		{
			this->z(std::asin(Mathf::clamp(m21, -1.0f, 1.0f)));
			if (std::abs(m21) < 0.99999f)
			{
				this->x(std::atan2(-m23, m22));
				this->y(std::atan2(-m31, m11));
			}
			else
			{
				this->x(0.0f);
				this->y(std::atan2(m13, m33));
			}

		}
		else if (order == xzy)
		{
			this->z(std::asin(-Mathf::clamp(m12, -1.0f, 1.0f)));
			if (std::abs(m12) < 0.99999f)
			{
				this->x(std::atan2(m32, m22));
				this->y(std::atan2(m13, m11));
			}
			else {
				this->x(std::atan2(-m23, m33));
				this->y(0.0f);
			}
		}
		else {
			// Order undefined
		}

		if (update && _onChange)
			_onChange();

		return *this;
	}
	EulerAngle& EulerAngle::setFromQuaternion(const Quat& q, RotSeq order, 
		bool update)
	{
		/*Mat4 matrix;
		if (!order)
		{
			order = this->_order;
		}*/
		return *this;
	}
    RotSeq EulerAngle::order() const
    {
        return this->_order;
    }
}
