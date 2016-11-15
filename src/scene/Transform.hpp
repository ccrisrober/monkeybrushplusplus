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

#ifndef __MB_TRANSFORM__
#define __MB_TRANSFORM__

#include "../maths/Quat.hpp"
#include "../maths/EulerAngle.hpp"
#include "../maths/Vect3.hpp"
#include "../maths/Mat4.hpp"

namespace MB {
	class Transform {
	public:
		Transform()
			: _position(Vect3::createFromScalar(0.0f))
			, _rotation(EulerAngle())
			, _quaternion(Quat())
			, _scale(Vect3::createFromScalar(1.0f))
			, _matrix(Mat4())
			, _matrixWorld(Mat4())
			, _autoUpdate(true)
			, _matrixWorldNeedUpdate(false)
		{
			std::function<void()> cbRotation([=]() {
				//this->quaternion = this->quaternion.setFromEuler(this->rotation);
			});
			_rotation.setCallback(cbRotation);
			std::function<void()> cbQuaternion([=]() {
				//this->rotation = this->rotation.setFromQuaternion(this->quaternion, this->rotation.order, false);
			});
			_quaternion.setCallback(cbQuaternion);
		}
		Vect3& position() {
			return this->_position;
		}
		EulerAngle& rotation() {
			return this->_rotation;
		}
		Quat& quaternion() {
			return this->_quaternion;
		}
		Vect3& scale() {
			return this->_scale;
		}
		void translateX(float dist) {
			this->_translateOnAxis(Vect3(1.0f, 0.0f, 0.0f), dist);
		}
		void translateY(float dist) {
			this->_translateOnAxis(Vect3(0.0f, 1.0f, 0.0f), dist);
		}
		void translateZ(float dist) {
			this->_translateOnAxis(Vect3(0.0f, 0.0f, 1.0f), dist);
		}
		void rotateX(float angle) {
			this->_rotateOnAxis(Vect3::xAxis, angle);
		};
		void rotateY(float angle) {
			this->_rotateOnAxis(Vect3::yAxis, angle);
		};
		void rotateZ(float angle) {
			this->_rotateOnAxis(Vect3::zAxis, angle);
		};
		void updateMatrix()
		{
			this->_matrix.compose(this->_position, this->_quaternion, this->_scale);
			this->_matrixWorldNeedUpdate = true;
		};
		Vect3 localWorld(Vect3 v)
		{
			return Vect3();
			//return v.applyMat4(this._matrixWorld);
		};
		Vect3 worldToLocal(Vect3 v)
		{
			return Vect3();
			//Mat4 mat;
			//return v.applyMat4(mat.inverse(this._matrixWorld));
		};
	protected:
		void _translateOnAxis(const Vect3& axis, float dist) {
			Vect3 v;
			//v.copy(axis).applyQuat(this->_quaternion);
			this->_position = this->_position.add(v.multByScalar(dist));
		};
		void _rotateOnAxis(Vect3 axis, float angle) {
			Quat q1;
			//q1.setFromAxisAngle(axis, angle);
			//this->_quaternion = this->_quaternion.mult(q1);
		};
		Vect3 _position;
		EulerAngle _rotation;
		Quat _quaternion;
		Vect3 _scale;

		Mat4 _matrix;
		Mat4 _matrixWorld;
		bool _autoUpdate;
		bool _matrixWorldNeedUpdate;
	};
}

#endif /* __MB_TRANSFORM__ */