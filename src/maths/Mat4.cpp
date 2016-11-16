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

#include "Mat4.hpp"
#include "Quat.hpp"

namespace MB
{
	Mat4::Mat4()
	{
		static const float _ident[] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};
		this->_values = std::vector<float>(_ident, _ident + sizeof(_ident) / sizeof(float));
	}
	Mat4::Mat4(const std::vector<float> values)
	{
		this->_values = values;
	}
	float Mat4::determinant() const
	{
		float
			a00 = this->_values[0], a01 = this->_values[1], a02 = this->_values[2], a03 = this->_values[3],
			a10 = this->_values[4], a11 = this->_values[5], a12 = this->_values[6], a13 = this->_values[7],
			a20 = this->_values[8], a21 = this->_values[9], a22 = this->_values[10], a23 = this->_values[11],
			a30 = this->_values[12], a31 = this->_values[13], a32 = this->_values[14], a33 = this->_values[15];

		float
			det00 = a00 * a11 - a01 * a10,
			det01 = a00 * a12 - a02 * a10,
			det02 = a00 * a13 - a03 * a10,
			det03 = a01 * a12 - a02 * a11,
			det04 = a01 * a13 - a03 * a11,
			det05 = a02 * a13 - a03 * a12,
			det06 = a20 * a31 - a21 * a30,
			det07 = a20 * a32 - a22 * a30,
			det08 = a20 * a33 - a23 * a30,
			det09 = a21 * a32 - a22 * a31,
			det10 = a21 * a33 - a23 * a31,
			det11 = a22 * a33 - a23 * a32;

		// Calculate the determinant
		return (det00 * det11 - det01 * det10 + det02 * det09 + det03 * det08 - det04 * det07 + det05 * det06);
	}
	void Mat4::compose(Vect3& position, Quat& quaternion, Vect3& scale)
	{
		/// ROTATION
		float x = quaternion.x(), 
			y = quaternion.y(),
			z = quaternion.z(), 
			w = quaternion.w();
		float x2 = x + x, y2 = y + y, z2 = z + z;
		float xx = x * x2, xy = x * y2, xz = x * z2;
		float yy = y * y2, yz = y * z2, zz = z * z2;
		float wx = w * x2, wy = w * y2, wz = w * z2;

		this->_values[0] = 1.0f - (yy + zz);
		this->_values[4] = xy - wz;
		this->_values[8] = xz + wy;

		this->_values[1] = xy + wz;
		this->_values[5] = 1.0f - (xx + zz);
		this->_values[9] = yz - wx;

		this->_values[2] = xz - wy;
		this->_values[6] = yz + wx;
		this->_values[10] = 1.0 - (xx + yy);

		// last column
		this->_values[3] = 0.0f;
		this->_values[7] = 0.0f;
		this->_values[11] = 0.0f;

		// bottom row
		this->_values[12] = 0.0f;
		this->_values[13] = 0.0f;
		this->_values[14] = 0.0f;
		this->_values[15] = 1.0f;

		/// SCALE
		x = scale.x();
		y = scale.y();
		z = scale.z();
		this->_values[0] *= x; this->_values[4] *= y; this->_values[8] *= z;
		this->_values[1] *= x; this->_values[5] *= y; this->_values[9] *= z;
		this->_values[2] *= x; this->_values[6] *= y; this->_values[10] *= z;
		this->_values[3] *= x; this->_values[7] *= y; this->_values[11] *= z;

		/// POSITION
		this->_values[12] = position.x();
		this->_values[13] = position.y();
		this->_values[14] = position.z();
	}
	void Mat4::decompose(Vect3& /*position*/, Quat& /*quaternion*/, Vect3& /*scale*/)
	{

	}
	void Mat4::set(
		float e11, float e12, float e13, float e14,
		float e21, float e22, float e23, float e24,
		float e31, float e32, float e33, float e34,
		float e41, float e42, float e43, float e44)
	{
		this->_values[0] = e11; this->_values[4] = e12; this->_values[8] = e13; this->_values[12] = e14;
		this->_values[1] = e21; this->_values[5] = e22; this->_values[9] = e23; this->_values[13] = e24;
		this->_values[2] = e31; this->_values[6] = e32; this->_values[10] = e33; this->_values[14] = e34;
		this->_values[3] = e41; this->_values[7] = e42; this->_values[11] = e43; this->_values[15] = e44;
	}
	Mat4 Mat4::perspective(const float& fovy, const float& aspect, 
		const float& near, const float& far)
	{
		float 
			f = 1.0f / std::tan(fovy / 2.0f),
			nf = 1.0f / (near - far);

		std::vector<float> out(16);

		out[0] = f / aspect;
		out[1] = 0.0f;
		out[2] = 0.0f;
		out[3] = 0.0f;
		out[4] = 0.0f;
		out[5] = f;
		out[6] = 0.0f;
		out[7] = 0.0f;
		out[8] = 0.0f;
		out[9] = 0.0f;
		out[10] = (far + near) * nf;
		out[11] = -1.0f;
		out[12] = 0.0f;
		out[13] = 0.0f;
		out[14] = (2.0f * far * near) * nf;
		out[15] = 0.0f;

		return Mat4(out);
	}
	Mat4 Mat4::orthographic(const float& left, const float& right, const float& bottom, 
		const float& top, const float& near, const float& far)
	{
		float
			rl = (right - left),
			tb = (top - bottom),
			fn = (far - left);
		std::vector<float> out(16);

		out[0] = 2.0f / rl;
		out[1] = 0.0f;
		out[2] = 0.0f;
		out[3] = 0.0f;
		out[4] = 0.0f;
		out[5] = 2.0f / tb;
		out[6] = 0.0f;
		out[7] = 0.0f;
		out[8] = 0.0f;
		out[9] = 0.0f;
		out[10] = -2.0f / fn;
		out[11] = 0.0f;
		out[12] = -(left + right) / rl;
		out[13] = -(top + bottom) / tb;
		out[14] = -(far + near) / fn;
		out[15] = 1.0f;

		return Mat4(out);
	}
}