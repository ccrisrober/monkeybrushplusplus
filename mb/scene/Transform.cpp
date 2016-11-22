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

#include "Transform.hpp"

namespace MB
{
	Transform::Transform()
	: _position(Vect3::createFromScalar(0.0f))
	, _rotation(EulerAngle())
	, _quaternion(Quat())
	, _scale(Vect3::createFromScalar(1.0f))
	, _matrix(Mat4())
	, _matrixWorld(Mat4())
	, _autoUpdate(true)
	, _matrixWorldNeedUpdate(false)
	{
		std::function<void()> cbRotation([&]()
		{
			this->_quaternion = this->_quaternion.setFromEuler(this->_rotation);
		});
		_rotation.setCallback(cbRotation);
		std::function<void()> cbQuaternion([=]()
		{
			this->_rotation = this->_rotation.setFromQuaternion(this->_quaternion, this->_rotation.order(), false);
		});
		_quaternion.setCallback(cbQuaternion);
	}
	Vect3& Transform::position()
	{
		return this->_position;
	}
	EulerAngle& Transform::rotation()
	{
		return this->_rotation;
	}
	Quat& Transform::quaternion()
	{
		return this->_quaternion;
	}
	Vect3& Transform::scale()
	{
		return this->_scale;
	}
	void Transform::translateX(float dist)
	{
		this->_translateOnAxis(Vect3(1.0f, 0.0f, 0.0f), dist);
	}
	void Transform::translateY(float dist)
	{
		this->_translateOnAxis(Vect3(0.0f, 1.0f, 0.0f), dist);
	}
	void Transform::translateZ(float dist)
	{
		this->_translateOnAxis(Vect3(0.0f, 0.0f, 1.0f), dist);
	}
	void Transform::rotateX(float angle)
	{
		this->_rotateOnAxis(Vect3::xAxis, angle);
    }
	void Transform::rotateY(float angle)
	{
		this->_rotateOnAxis(Vect3::yAxis, angle);
    }
	void Transform::rotateZ(float angle)
	{
		this->_rotateOnAxis(Vect3::zAxis, angle);
    }
	void Transform::updateMatrix()
	{
		this->_matrix.compose(this->_position, this->_quaternion, this->_scale);
		this->_matrixWorldNeedUpdate = true;
    }
    Vect3 Transform::localWorld(const Vect3 /*v*/)
	{
		return Vect3();
		//return v.applyMat4(this._matrixWorld);
    }
    Vect3 Transform::worldToLocal(const Vect3 /*v*/)
	{
		return Vect3();
		//Mat4 mat;
		//return v.applyMat4(mat.inverse(this._matrixWorld));
    }
    void Transform::_translateOnAxis(const Vect3& /*axis*/, float dist)
	{
		Vect3 v;
		//v.copy(axis).applyQuat(this->_quaternion);
		this->_position = this->_position.add(v.multByScalar(dist));
    }
    void Transform::_rotateOnAxis(const Vect3 /*axis*/, float /*angle*/)
	{
		Quat q1;
		//q1.setFromAxisAngle(axis, angle);
		//this->_quaternion = this->_quaternion.mult(q1);
    }
}
