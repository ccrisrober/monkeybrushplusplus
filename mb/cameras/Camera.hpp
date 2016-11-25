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

#ifndef __MB_CAMERA__
#define __MB_CAMERA__

#include <mb/api.h>

#include "../maths/Mat4.hpp"
#include "../scene/Transform.hpp"

namespace MB
{
	class Camera
	{
	public:
		MB_API
		Camera(float near_ = 0.1f, float far_ = 1000.0f);
		MB_API
		Mat4 projectionMatrix() const;
		MB_API
		Mat4 viewMatrix() const;
		MB_API
		Transform& transform();
		MB_API
		void setNearFar(float near, float far);
		MB_API
		float near() const;
		MB_API
		void near(float near);
		MB_API
		float far() const;
		MB_API
		void far(float far);
	protected:
		Mat4 _viewMatrix;
		Mat4 _projectionMatrix;
		Transform _transform;
		float _near;
		float _far;

		virtual void updateProjectionMatrix() = 0;
	};
}

#endif /* __MB_CAMERA__ */
