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

#include "PerspectiveCamera.hpp"

namespace mb
{
	PerspectiveCamera::PerspectiveCamera(float fov_, float aspect_, float near_, float far_)
		: Camera(near_, far_)
		, _fov(fov_)
		, _aspect(aspect_)
	{
		updateProjectionMatrix();
	}
	std::ostream& operator<<(std::ostream & os, const PerspectiveCamera & o)
	{
		os << "PerspectiveCamera (" << std::endl;
		os << "\tFOV   : " << o._fov << std::endl;
		os << "\tASPECT: " << o._aspect << std::endl;
		os << "\tNEAR  : " << o._near << std::endl;
		os << "\tFAR   : " << o._far << std::endl;
		os << ")";
		return os;
	}
	void PerspectiveCamera::setWindowSize(int width, int height)
	{
		this->_aspect = (float)width / (float)height;
		updateProjectionMatrix();
	}
	void PerspectiveCamera::fov(float fov_)
	{
		this->_fov = fov_;
		updateProjectionMatrix();
	}
	void PerspectiveCamera::updateProjectionMatrix()
	{
		_projectionMatrix = Mat4::perspective(_fov, _aspect, _near, _far);
	}
}
