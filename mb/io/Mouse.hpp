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

#include "../constants/Constants.hpp"
#include "../Includes.hpp"

using MB::ctes::MouseButton;

#define MOUSE_LEFTBUTTON 0
#define MOUSE_CENTERBUTTON 1
#define MOUSE_RIGHTBUTTON 2 

namespace MB
{
	class Mouse
	{
	public:
		virtual ~Mouse() {}
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
		GLFWMouse()
			: Mouse()
			, _x(0)
			, _y(0)
			, _prevX(0)
			, _prevY(0)
			, _wheelX(0)
			, _wheelY(0)
			, _prevWheelX(0)
			, _prevWheelY(0)
		{
			_current[MOUSE_LEFTBUTTON].state = GLFW_RELEASE;
			_current[MOUSE_CENTERBUTTON].state = GLFW_RELEASE;
			_current[MOUSE_RIGHTBUTTON].state = GLFW_RELEASE;

			_previous[MOUSE_LEFTBUTTON].state = GLFW_RELEASE;
			_previous[MOUSE_CENTERBUTTON].state = GLFW_RELEASE;
			_previous[MOUSE_RIGHTBUTTON].state = GLFW_RELEASE;
		}
		virtual ~GLFWMouse() {}
		virtual int mouseX()
		{
			return _x;
		}
		virtual int mouseY()
		{
			return _y;
		}
		virtual int previousMouseX()
		{
			return _prevX;
		}
		virtual int previousMouseY()
		{
			return _prevY;
		}
		virtual int mouseWheelX()
		{
			return _wheelX;
		}
		virtual int mouseWheelY()
		{
			return _wheelY;
		}
		virtual int deltaX(int val)
		{
			if (_x != _prevX)
			{
				return _x - val;
			}
			return 0;
		}
		virtual int deltaY(int val)
		{
			if (_y != _prevY)
			{
				return _y - val;
			}
			return 0;
		}
		virtual bool buttonRelease(MouseButton button)
		{
			switch (button)
			{
			case MouseButton::Left:
				return _current[MOUSE_LEFTBUTTON].state == GLFW_RELEASE && _previous[MOUSE_LEFTBUTTON].state == GLFW_PRESS;
			case MouseButton::Middle:
				return _current[MOUSE_CENTERBUTTON].state == GLFW_RELEASE && _previous[MOUSE_CENTERBUTTON].state == GLFW_PRESS;
			case MouseButton::Right:
				return _current[MOUSE_RIGHTBUTTON].state == GLFW_RELEASE && _previous[MOUSE_RIGHTBUTTON].state == GLFW_PRESS;
			default:
				return false;
			}
		}
		virtual bool buttonPress(MouseButton button)
		{
			switch (button)
			{
			case MouseButton::Left:
				return _current[MOUSE_LEFTBUTTON].state == GLFW_PRESS;
			case MouseButton::Middle:
				return _current[MOUSE_CENTERBUTTON].state == GLFW_PRESS;
			case MouseButton::Right:
				return _current[MOUSE_RIGHTBUTTON].state == GLFW_PRESS;
			default:
				return false;
			}
		}
		virtual bool singleButtonPress(MouseButton button)
		{
			switch (button)
			{
			case MouseButton::Left:
				return _current[MOUSE_LEFTBUTTON].state == GLFW_PRESS && _previous[MOUSE_LEFTBUTTON].state == GLFW_RELEASE;
			case MouseButton::Middle:
				return _current[MOUSE_CENTERBUTTON].state == GLFW_PRESS && _previous[MOUSE_CENTERBUTTON].state == GLFW_RELEASE;
			case MouseButton::Right:
				return _current[MOUSE_RIGHTBUTTON].state == GLFW_PRESS && _previous[MOUSE_RIGHTBUTTON].state == GLFW_RELEASE;
			default:
				return false;
			}
		}
		virtual void update()
		{
			_prevWheelX = _wheelX;
			_prevWheelY = _wheelY;
			_prevX = _x;
			_prevY = _y;
			_wheelY = 0;
			memcpy(_previous, _current, sizeof(_current));
		}

		void onMouseMove(int x, int y)
		{
			_x = x;
			_y = y;
		}

		void onMouseButtonEvent(int e, int action)
		{
			switch (e)
			{
				case GLFW_MOUSE_BUTTON_LEFT:
					_current[MOUSE_LEFTBUTTON].state = static_cast<uint8_t>(action);
					_current[MOUSE_LEFTBUTTON].clicks = 1;
					break;
				case GLFW_MOUSE_BUTTON_MIDDLE:
					_current[MOUSE_CENTERBUTTON].state = static_cast<uint8_t>(action);
					_current[MOUSE_CENTERBUTTON].clicks = 1;
					break;
				case GLFW_MOUSE_BUTTON_RIGHT:
					_current[MOUSE_RIGHTBUTTON].state = static_cast<uint8_t>(action);
					_current[MOUSE_RIGHTBUTTON].clicks = 1;
				break;
			}
		}

		void onMouseWheelEvent(int xoffset, int yoffset)
		{
			_wheelX = xoffset;
			_wheelY = yoffset;
		}
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