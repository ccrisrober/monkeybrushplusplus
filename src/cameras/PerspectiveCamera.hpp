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

#ifndef __MB_PERSPECTIVE_CAMERA__
#define __MB_PERSPECTIVE_CAMERA__

#include "Camera.hpp"
#include <iostream>

namespace MB
{
	class PerspectiveCamera: public Camera
	{
	public:
		PerspectiveCamera(float fov_ = 45.0f, float aspect_ = 1.0f, float near_ = 0.1f, float far_ = 1000.0f)
			: Camera(near_, far_)
			, _fov(fov_)
			, _aspect(aspect_)
		{
			updateProjectionMatrix();
		}
		friend std::ostream& operator <<(std::ostream& os, const PerspectiveCamera& o)
		{
			os << "PerspectiveCamera (" << std::endl;
			os << "\tFOV   : " << o._fov << std::endl;
			os << "\tASPECT: " << o._aspect << std::endl;
			os << "\tNEAR  : " << o._near << std::endl;
			os << "\tFAR   : " << o._far << std::endl;
			os << ")";
			return os;
		}
		void setWindowSize(int width, int height)
		{
			this->_aspect = (float)width / (float)height;
			updateProjectionMatrix();
		}
		void fov(float fov_)
		{
			this->_fov = fov_;
			updateProjectionMatrix();
		}
	protected:
		virtual void updateProjectionMatrix()
		{
			_projectionMatrix = Mat4::perspective(_fov, _aspect, _near, _far);
		}
		float _fov;
		float _aspect;
	};
}

#endif /* __MB_PERSPECTIVE_CAMERA__ */
