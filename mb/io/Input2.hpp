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

#ifndef __MB_INPUT2__
#define __MB_INPUT2__

#include <mb/api.h>

#include "../Includes.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"

namespace MB
{
	class Input2
	{
	public:
		static void initialize();
		static void destroy();
		static MB::Keyboard* Keyboard();
		static MB::Mouse* Mouse();
		MB_API
		static bool isKeyPressed(Keyboard::Key key);
		MB_API
		static bool isKeyClicked(Keyboard::Key key);
		MB_API
		static bool KeyReleased(Keyboard::Key key);
		MB_API
		static int MouseX();
		MB_API
		static int MouseY();
		static Input2* instance();
		static int PreviousMouseX();
		static int PreviousMouseY();
		static int MouseWheelX();
		static int MouseWheelY();
		static int DeltaX(int val);
		static int DeltaY(int val);
		static bool MouseButtonPress(MouseButton button);
		static bool MouseButtonSinglePress(MouseButton button);
		static bool MouseButtonRelease(MouseButton button);
		static void update();
	protected:
		MB::Keyboard* _keyboard;
		MB::Mouse*    _mouse;

		static Input2 *_instance;
	};
}

#endif /* __MB_INPUT2__ */