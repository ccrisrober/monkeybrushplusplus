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

#include "OrthographicCamera.hpp"

namespace mb
{
	OrthographicCamera::OrthographicCamera(float left_, 
		float right_, float top_, float bottom_, float near_, 
		float far_)
	: Camera(near_, far_)
	, left(left_)
	, right(right_)
	, top(top_)
	, bottom(bottom_)
	{
		updateProjectionMatrix();
	}
	std::ostream& operator << (std::ostream& os, const OrthographicCamera& o)
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
	void OrthographicCamera::updateProjectionMatrix()
	{
		_projectionMatrix = Mat4::orthographic(left, right, 
			bottom, top, _near, _far);
	}
}
