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

// TODO: Usar std::array en vez de std::vector!
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
	void Mat4::copy(const Mat4& m)
	{
		this->_values = m._values;
	}
	Mat4 Mat4::mult2(const Mat4& a, const Mat4& b)
	{
		std::vector<float> ae = a._values;
		std::vector<float> be = b._values;
		std::vector<float> te(16);

		float a11 = ae[0], a12 = ae[4], a13 = ae[8], a14 = ae[12];
		float a21 = ae[1], a22 = ae[5], a23 = ae[9], a24 = ae[13];
		float a31 = ae[2], a32 = ae[6], a33 = ae[10], a34 = ae[14];
		float a41 = ae[3], a42 = ae[7], a43 = ae[11], a44 = ae[15];

		float b11 = be[0], b12 = be[4], b13 = be[8], b14 = be[12];
		float b21 = be[1], b22 = be[5], b23 = be[9], b24 = be[13];
		float b31 = be[2], b32 = be[6], b33 = be[10], b34 = be[14];
		float b41 = be[3], b42 = be[7], b43 = be[11], b44 = be[15];

		te[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
		te[4] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
		te[8] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
		te[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

		te[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
		te[5] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
		te[9] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
		te[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

		te[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
		te[6] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
		te[10] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
		te[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

		te[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
		te[7] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
		te[11] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
		te[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

		return Mat4(te);
	}
	Mat4 Mat4::lookAt(const Vect3& pos, const Vect3& target, const Vect3& up)
	{
		/*if (pos.isEquals(target)) {
			return this.identity;
		}*/

		Vect3 z = Vect3::sub(pos, target);
		z.normalize();

		Vect3 x = Vect3::cross(up, z);
		x.normalize();
		Vect3 y = Vect3::cross(z, x);
		y.normalize();

		std::vector<float> out = {
				x.x(),                y.x(),                z.x(),     0.0f,
				x.y(),                y.y(),                z.y(),     0.0f,
				x.z(),                y.z(),                z.z(),     0.0f,
				-Vect3::dot(x, pos), -Vect3::dot(y, pos), -Vect3::dot(z, pos),     1.0f
		};
		return Mat4(out);
    }
}