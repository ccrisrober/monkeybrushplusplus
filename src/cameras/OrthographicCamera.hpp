/*
* Copyright (c) 2016 maldicion069
*
* Authors: Cristian Rodr�guez Bernal <ccrisrober@gmail.com>
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

#ifndef __MB_ORTHOGRAPHIC_CAMERA__
#define __MB_ORTHOGRAPHIC_CAMERA__

#include "Camera.hpp"
#include <iostream>

namespace MB
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left_, float right_, float top_, float bottom_, float near_ = 0.1f, float far_ = 1000.0f)
			: Camera(near_, far_)
			, left(left_)
			, right(right_)
			, top(top_)
			, bottom(bottom_)
		{
			updateProjectionMatrix();
		}
		friend std::ostream& operator <<(std::ostream& os, const OrthographicCamera& o)
		{
			os << "OrthographicCamera (" << std::endl;
			os << "\tLEFT  : " << o.left << std::endl;
			os << "\tRIGHT : " << o.right << std::endl;
			os << "\tTOP  : " << o.top << std::endl;
			os << "\tBOTTOM : " << o.bottom << std::endl;
			os << "\tNEAR  : " << o._near << std::endl;
			os << "\tFAR   : " << o._far << std::endl;
			os << ")";
			return os;
		}
		float left;
		float right;
		float top;
		float bottom;
	protected:
		virtual void updateProjectionMatrix()
		{
			_projectionMatrix = Mat4::orthographic(left, right, bottom, top, _near, _far);
		}
	};
}

#endif /* __MB_ORTHOGRAPHIC_CAMERA__ */