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

namespace mb
{
	class MoveComponent : public mb::Component
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
	class RotateComponent : public mb::Component
	{
	public:
	#ifdef MB_USE_RAPIDJSON
		MB_API
        RotateComponent(const rapidjson::Value& config)
        : RotateComponent(_axisFromString(config["axis"].GetString( )))
        {
        	if (config.HasMember("rotate"))
        	{
        		bool rotate = config["rotate"].GetBool();
        		setRotate(rotate);
        	}
		}
		Axis _axisFromString(const std::string& _axis_)
		{
			if (_axis_ == "X")
			{
				return mb::Axis::x;
			} else if (_axis_ == "Y")
			{
				return mb::Axis::y;
			} else if (_axis_ == "Z")
			{
				return mb::Axis::z;
			}
			throw;
		}
	#endif

		MB_API
		RotateComponent(Axis axis, float velocity = 1.0f, bool rotate = false);
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
	class ScaleComponent : public mb::Component
	{
	public:
		MB_API
		ScaleComponent();
		MB_API
		virtual void update(float /*dt*/);
	protected:
		float _inc;
	};
	class PrintPosition : public mb::Component
	{
	public:
		MB_API
		PrintPosition();
		MB_API
		virtual void update(float);
	};
};

#endif /* __MB_HELPERS__ */
