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

#ifndef __MB_MOUSE__
#define __MB_MOUSE__

#include <mb/api.h>
#include <cstring>

#include "../constants/Constants.hpp"
#include "../Includes.hpp"

using mb::ctes::MouseButton;

namespace mb
{
	class Mouse
	{
	public:
		virtual ~Mouse();
		virtual int mouseX() = 0;
		virtual int mouseY() = 0;
		virtual int previousMouseX() = 0;
		virtual int previousMouseY() = 0;
		virtual int mouseWheelX() = 0;
		virtual int mouseWheelY() = 0;
		virtual int deltaX(int val) = 0;
		virtual int deltaY(int val) = 0;
		virtual bool buttonRelease(MouseButton button) = 0;
		virtual bool buttonPress(MouseButton button) = 0;
		virtual bool singleButtonPress(MouseButton button) = 0;
		virtual void update() = 0;
	};
	class GLFWMouse : public Mouse
	{
	public:
		MB_API
		GLFWMouse();
		MB_API
		virtual ~GLFWMouse();
		MB_API
		virtual int mouseX();
		MB_API
		virtual int mouseY();
		MB_API
		virtual int previousMouseX();
		MB_API
		virtual int previousMouseY();
		MB_API
		virtual int mouseWheelX();
		MB_API
		virtual int mouseWheelY();
		MB_API
		virtual int deltaX(int val);
		MB_API
		virtual int deltaY(int val);
		MB_API
		virtual bool buttonRelease(MouseButton button);
		MB_API
		virtual bool buttonPress(MouseButton button);
		MB_API
		virtual bool singleButtonPress(MouseButton button);
		MB_API
		virtual void update();

		void onMouseMove(int x, int y);
		void onMouseButtonEvent(int e, int action);
		void onMouseWheelEvent(int xoffset, int yoffset);
		struct GLFWMouseState
		{
			short clicks = 0;
			short state;
		};
	protected:
		int _x;
		int _y;
		int _prevX;
		int _prevY;
		int _wheelX;
		int _wheelY;
		int _prevWheelX;
		int _prevWheelY;
		GLFWMouseState _current[3];
		GLFWMouseState _previous[3];
	};
}

#endif /* __MB_MOUSE__ */