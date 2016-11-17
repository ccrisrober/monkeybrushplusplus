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

#ifndef __MB_TRANSFORM__
#define __MB_TRANSFORM__

#include "../maths/Quat.hpp"
#include "../maths/EulerAngle.hpp"
#include "../maths/Vect3.hpp"
#include "../maths/Mat4.hpp"

namespace MB
{
	class Transform
	{
	public:
		Transform();
		Vect3& position();
		EulerAngle& rotation();
		Quat& quaternion();
		Vect3& scale();
		void translateX(float dist);
		void translateY(float dist);
		void translateZ(float dist);
		void rotateX(float angle);
		void rotateY(float angle);
		void rotateZ(float angle) ;
		void updateMatrix();
        Vect3 localWorld(const Vect3 v);
        Vect3 worldToLocal(const Vect3 v);
	protected:
        void _translateOnAxis(const Vect3& axis, float dist);
        void _rotateOnAxis(const Vect3 axis, float angle);
		Vect3 _position;
		EulerAngle _rotation;
		Quat _quaternion;
		Vect3 _scale;

	public:
		Mat4 _matrix;
		Mat4 _matrixWorld;
		Mat4 matrix() const {
			return this->_matrix;
		}
		Mat4 matrixWorld() const {
			return this->_matrixWorld;
		}
		bool _autoUpdate;
		bool _matrixWorldNeedUpdate;
	};
}

#endif /* __MB_TRANSFORM__ */
