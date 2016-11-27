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

#include <mb/api.h>

#include "Camera.hpp"
#include <iostream>

namespace mb
{
	class PerspectiveCamera: public Camera
	{
	public:
		MB_API
		PerspectiveCamera(float fov_ = 45.0f, 
			float aspect_ = 1.0f, float near_ = 0.1f, 
			float far_ = 1000.0f);
		MB_API
		friend std::ostream& operator <<(std::ostream& os, 
			const PerspectiveCamera& o);
		MB_API
		void setWindowSize(int width, int height);
		MB_API
		void fov(float fov_);
	protected:
		virtual void updateProjectionMatrix();
		float _fov;
		float _aspect;
	};
}

#endif /* __MB_PERSPECTIVE_CAMERA__ */
