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

#include "Quat.hpp"

namespace MB
{
	Quat::Quat(float x, float y, float z, float w)
	{
		this->_values.resize(4);
		this->_values[0] = x;
		this->_values[1] = y;
		this->_values[2] = z;
		this->_values[3] = w;
	}
    Quat::Quat(const Quat& q)
    {
        this->_values.resize(4);
        this->_values[0] = q.x();
        this->_values[1] = q.y();
        this->_values[2] = q.z();
        this->_values[3] = q.w();
    }
    Quat& Quat::operator=(const Quat& q)
    {
        return copy(q);
    }
    Quat& Quat::copy(const Quat& q) {
        x(q.x());
        y(q.y());
        z(q.z());
        w(q.w());
        return *this;
    }

	void Quat::setCallback(std::function<void()> f)
	{
		this->_onChange = f;
	}
	float Quat::x() const
	{
		return this->_values[0];
	}
	float Quat::y() const
	{
		return this->_values[1];
	}
	float Quat::z() const
	{
		return this->_values[2];
	}
	float Quat::w() const
	{
		return this->_values[3];
	}
	void Quat::x(const float& v)
	{
		this->_values[0] = v;

		if (_onChange)
			_onChange();
	}
	void Quat::y(const float& v)
	{
		this->_values[1] = v;

		if (_onChange)
			_onChange();
	}
	void Quat::z(const float& v)
	{
		this->_values[2] = v;

		if (_onChange)
			_onChange();
	}
	void Quat::w(const float& v)
	{
		this->_values[3] = v;

		if (_onChange)
			_onChange();
	}
	float Quat::pitch()
	{
		float
			x = this->x(),
			y = this->y(),
			z = this->z(),
			w = this->w();

		return std::atan2(2.0f * (y * z + w * x), w * w - x * x - y * y + z * z);
	}
	float Quat::yaw()
	{
		return std::asin(2.0f * (this->x() * this->z() - this->w() * this->y()));
	}
	float Quat::roll()
	{
		float
			x = this->x(),
			y = this->y(),
			z = this->z(),
			w = this->w();

		return std::atan2(2.0f * (x * y + w * z), w * w + x * x - y * y - z * z);
	}
	float Quat::dot(const Quat& q1, const Quat& q2)
	{
		return q1.x() * q2.x() + q1.y() * q2.y() + q1.z() * q2.z() + q1.w() * q2.w();
	}
	void Quat::reset()
	{
		this->_values[0] = 0.0f;
		this->_values[1] = 0.0f;
		this->_values[2] = 0.0f;
		this->_values[3] = 1.0f;

		if (_onChange)	_onChange();
	}
	Quat& Quat::inverse()
	{
		float dot = Quat::dot(*this, *this);

		if (!dot) {
			this->reset();

			return *this;
		}

		float invDot = dot ? 1.0f / dot : 0.0f;

		this->_values[0] *= -invDot;
		this->_values[1] *= -invDot;
		this->_values[2] *= -invDot;
		this->_values[3] *= -invDot;

		return *this;
	}
	Quat& Quat::conjugate()
	{
		this->_values[0] = -this->_values[0];
		this->_values[1] = -this->_values[1];
		this->_values[2] = -this->_values[2];

		if (_onChange)	_onChange();

		return *this;
	}
	Quat& Quat::setFromAxisAngle(const Vect3& axis, float angle)
	{
		// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm
		//     Assumes axis is normalized
		float
			halfAngle = angle / 2.0f,
			s = std::sin(halfAngle);

		this->_values[0] = axis.x() * s;
		this->_values[1] = axis.y() * s;
		this->_values[2] = axis.z() * s;
		this->_values[3] = std::cos(halfAngle);

		if (_onChange)	_onChange();

		return *this;
	}
    Quat& Quat::setFromRotationMatrix(const Mat4& mat)
    {
        // Based on http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
        float m00 = mat._values[0], m01 = mat._values[4], m02 = mat._values[8],
            m10 = mat._values[1], m11 = mat._values[5], m12 = mat._values[9],
            m20 = mat._values[2], m21 = mat._values[6], m22 = mat._values[10],

            tr = m00 + m11 + m22,
            s;

        if (tr > 0.0f)
        {
            s = 0.5f / std::sqrt(tr + 1.0f);
            this->_values[3] = 0.25f / s;
            this->_values[0] = (m21 - m12) * s;
            this->_values[1] = (m02 - m20) * s;
            this->_values[2] = (m10 - m01) * s;
        }
        else if (m00 > m11 && m00 > m22)
        {
            s = 2.0f * std::sqrt(1.0f + m00 - m11 - m22);
            this->_values[3] = (m21 - m12) / s;
            this->_values[0] = 0.25f * s;
            this->_values[1] = (m01 + m10) / s;
            this->_values[2] = (m02 + m20) / s;
        }
        else if (m11 > m22)
        {
            s = 2.0f * std::sqrt(1.0f + m11 - m00 - m22);
            this->_values[3] = (m02 - m20) / s;
            this->_values[0] = (m01 + m10) / s;
            this->_values[1] = 0.25f * s;
            this->_values[2] = (m12 + m21) / s;
        }
        else
        {
            s = 2.0f * std::sqrt(1.0f + m22 - m00 - m11);
            this->_values[3] = (m10 - m01) / s;
            this->_values[0] = (m02 + m20) / s;
            this->_values[1] = (m12 + m21) / s;
            this->_values[2] = 0.25f * s;
        }

        //this->onChange();

        return *this;
    }
	Quat& Quat::add(const Quat& q)
	{
		for (unsigned int i = 0; i < 4; ++i)
		{
			this->_values[i] += q._values[i];
		}
		return *this;
	}
	Quat& Quat::rem(const Quat& q)
	{
		for (unsigned int i = 0; i < 4; ++i)
		{
			this->_values[i] -= q._values[i];
		}
		return *this;
	}
	Quat& Quat::mult(const Quat& q)
	{
		float
			q1x = this->x(),
			q1y = this->y(),
			q1z = this->z(),
			q1w = this->w();

		float
			q2x = q.x(),
			q2y = q.y(),
			q2z = q.z(),
			q2w = q.w();

		this->_values[0] = q1x * q2w + q1w * q2x + q1y * q2z - q1z * q2y;
		this->_values[1] = q1y * q2w + q1w * q2y + q1z * q2x - q1x * q2z;
		this->_values[2] = q1z * q2w + q1w * q2z + q1x * q2y - q1y * q2x;
		this->_values[3] = q1w * q2w - q1x * q2x - q1y * q2y - q1z * q2z;

		return *this;
	}
	bool Quat::operator==(const Quat& other) const
	{
		return x() == other.x() && y() == other.y()
			&& z() == other.z() && w() == other.w();
	}
    Quat& Quat::setFromEuler(const EulerAngle& euler)
    {
        // Based on http://www.mathworks.com/matlabcentral/fileexchange/
        //     20696-function-to-convert-between-dcm-euler-angles-quaternions-
        //     and-euler-vectors/content/SpinCalc.m

        float s1 = std::sin(euler.x() / 2.0f);
        float s2 = std::sin(euler.y() / 2.0f);
        float s3 = std::sin(euler.z() / 2.0f);
        float c1 = std::cos(euler.x() / 2.0f);
        float c2 = std::cos(euler.y() / 2.0f);
        float c3 = std::cos(euler.z() / 2.0f);

        auto order = euler.order();
        if (order == xyz)
        {
            this->_values[0] = s1 * c2 * c3 + c1 * s2 * s3;
            this->_values[1] = c1 * s2 * c3 - s1 * c2 * s3;
            this->_values[2] = c1 * c2 * s3 + s1 * s2 * c3;
            this->_values[3] = c1 * c2 * c3 - s1 * s2 * s3;
        }
        else if (order == yxz)
        {
            this->_values[0] = s1 * c2 * c3 + c1 * s2 * s3;
            this->_values[1] = c1 * s2 * c3 - s1 * c2 * s3;
            this->_values[2] = c1 * c2 * s3 - s1 * s2 * c3;
            this->_values[3] = c1 * c2 * c3 + s1 * s2 * s3;
        }
        else if (order == zxy)
        {
            this->_values[0] = s1 * c2 * c3 - c1 * s2 * s3;
            this->_values[1] = c1 * s2 * c3 + s1 * c2 * s3;
            this->_values[2] = c1 * c2 * s3 + s1 * s2 * c3;
            this->_values[3] = c1 * c2 * c3 - s1 * s2 * s3;
        }
        else if (order == zyx)
        {
            this->_values[0] = s1 * c2 * c3 - c1 * s2 * s3;
            this->_values[1] = c1 * s2 * c3 + s1 * c2 * s3;
            this->_values[2] = c1 * c2 * s3 - s1 * s2 * c3;
            this->_values[3] = c1 * c2 * c3 + s1 * s2 * s3;
        }
        else if (order == yzx)
        {
            this->_values[0] = s1 * c2 * c3 + c1 * s2 * s3;
            this->_values[1] = c1 * s2 * c3 + s1 * c2 * s3;
            this->_values[2] = c1 * c2 * s3 - s1 * s2 * c3;
            this->_values[3] = c1 * c2 * c3 - s1 * s2 * s3;
        }
        else if (order == xzy)
        {
            this->_values[0] = s1 * c2 * c3 - c1 * s2 * s3;
            this->_values[1] = c1 * s2 * c3 - s1 * c2 * s3;
            this->_values[2] = c1 * c2 * s3 + s1 * s2 * c3;
            this->_values[3] = c1 * c2 * c3 + s1 * s2 * s3;
        }
        return *this;
    }
}
