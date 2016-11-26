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

#ifndef __MB_HELPERS__
#define __MB_HELPERS__

#include <mb/api.h>
#include "utils/macros.hpp"

#include "scene/Component.hpp"

namespace MB
{
	class MoveComponent : public MB::Component
	{
	public:
		MB_API
		MoveComponent();
		MB_API
		virtual void update(float dt);
	protected:
		float _delta;
		int _sign;
		float _velocity;
	};
	enum class Axis
	{
		x, y, z
	};
	class RotateComponent : public MB::Component
	{
	public:
		MB_API
		RotateComponent(Axis axis);
		//MB_API
		//void setAxis(Axis axis);
		MB_API
		virtual void update(float dt);
		MB_SYNTHESIZE_WRITEONLY(bool, _rotate, Rotate);
		MB_SYNTHESIZE_WRITEONLY(Axis, _axis, Axis);
	protected:
		float _delta;
		float _velocity;
	};
	class ScaleComponent : public MB::Component
	{
	public:
		MB_API
		ScaleComponent();
		MB_API
		virtual void update(float /*dt*/);
	protected:
		float _inc;
	};
	class PrintPosition : public MB::Component
	{
	public:
		MB_API
		PrintPosition();
		MB_API
		virtual void update(float);
	};
};

#endif /* __MB_HELPERS__ */