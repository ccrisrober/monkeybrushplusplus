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

#ifndef __MB_KEYBOARD__
#define __MB_KEYBOARD__

#include <mb/api.h>

#include <map>

#include "../Includes.hpp"

namespace MB
{
	class Keyboard
	{
	public:
		enum class Key
		{
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			Up,
			Down,
			Left,
			Right,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			Num1,
			Num2,
			Num3,
			Num4,
			Num5,
			Num6,
			Num7,
			Num8,
			Num9,
			Num0,
			Esc,
			Enter,
			Space,
			LShift,
			RShift,
			LAlt,
			RAlt
		};

		virtual ~Keyboard() { };

		virtual bool keyPress(const Key& k) = 0;
		virtual bool keyRelease(const Key& k) = 0;
		virtual bool singleKeyPress(const Key& k) = 0;
		virtual void update() = 0;
	};
	class GLFWKeyboard : public Keyboard
	{
	public:
		void onKeyUp(int code)
		{
			_current[code] = false;
		}
		void onKeyDown(int code)
		{
			_current[code] = true;
		}
		virtual bool keyPress(const Key& k)
		{
			int code = ConvertFromKey(k);
			return _current[code];
		}
		virtual bool keyRelease(const Key& k)
		{
			int code = ConvertFromKey(k);
			return _current[code] && _previous[code];
		}
		virtual bool singleKeyPress(const Key& k)
		{
			int code = ConvertFromKey(k);
			return _current[code] && !_previous[code];
		}
		virtual void update()
		{
			_previous = _current;
		}
	private:
		std::map<int, bool> _current;
		std::map<int, bool> _previous;

		int GLFWKeyboard::ConvertFromKey(Keyboard::Key k)
		{
			switch (k)
			{
			case Keyboard::Key::A:
				return GLFW_KEY_A;
			case Keyboard::Key::B:
				return GLFW_KEY_B;
			case Keyboard::Key::C:
				return GLFW_KEY_C;
			case Keyboard::Key::D:
				return GLFW_KEY_D;
			case Keyboard::Key::E:
				return GLFW_KEY_E;
			case Keyboard::Key::F:
				return GLFW_KEY_F;
			case Keyboard::Key::G:
				return GLFW_KEY_G;
			case Keyboard::Key::H:
				return GLFW_KEY_H;
			case Keyboard::Key::I:
				return GLFW_KEY_I;
			case Keyboard::Key::J:
				return GLFW_KEY_J;
			case Keyboard::Key::K:
				return GLFW_KEY_K;
			case Keyboard::Key::L:
				return GLFW_KEY_L;
			case Keyboard::Key::M:
				return GLFW_KEY_M;
			case Keyboard::Key::N:
				return GLFW_KEY_N;
			case Keyboard::Key::O:
				return GLFW_KEY_O;
			case Keyboard::Key::P:
				return GLFW_KEY_P;
			case Keyboard::Key::Q:
				return GLFW_KEY_Q;
			case Keyboard::Key::R:
				return GLFW_KEY_R;
			case Keyboard::Key::S:
				return GLFW_KEY_S;
			case Keyboard::Key::T:
				return GLFW_KEY_T;
			case Keyboard::Key::U:
				return GLFW_KEY_U;
			case Keyboard::Key::V:
				return GLFW_KEY_V;
			case Keyboard::Key::W:
				return GLFW_KEY_W;
			case Keyboard::Key::X:
				return GLFW_KEY_X;
			case Keyboard::Key::Y:
				return GLFW_KEY_Y;
			case Keyboard::Key::Z:
				return GLFW_KEY_Z;
			case Keyboard::Key::Up:
				return GLFW_KEY_UP;
			case Keyboard::Key::Down:
				return GLFW_KEY_DOWN;
			case Keyboard::Key::Left:
				return GLFW_KEY_LEFT;
			case Keyboard::Key::Right:
				return GLFW_KEY_RIGHT;
			case Keyboard::Key::Space:
				return GLFW_KEY_SPACE;
			case Keyboard::Key::F1:
				return GLFW_KEY_F1;
			case Keyboard::Key::F2:
				return GLFW_KEY_F2;
			case Keyboard::Key::F3:
				return GLFW_KEY_F3;
			case Keyboard::Key::F4:
				return GLFW_KEY_F4;
			case Keyboard::Key::F5:
				return GLFW_KEY_F5;
			case Keyboard::Key::F6:
				return GLFW_KEY_F6;
			case Keyboard::Key::F7:
				return GLFW_KEY_F7;
			case Keyboard::Key::F8:
				return GLFW_KEY_F8;
			case Keyboard::Key::F9:
				return GLFW_KEY_F9;
			case Keyboard::Key::F10:
				return GLFW_KEY_F10;
			case Keyboard::Key::F11:
				return GLFW_KEY_F11;
			case Keyboard::Key::F12:
				return GLFW_KEY_F12;
			case Keyboard::Key::Num0:
				return GLFW_KEY_0;
			case Keyboard::Key::Num1:
				return GLFW_KEY_1;
			case Keyboard::Key::Num2:
				return GLFW_KEY_2;
			case Keyboard::Key::Num3:
				return GLFW_KEY_3;
			case Keyboard::Key::Num4:
				return GLFW_KEY_4;
			case Keyboard::Key::Num5:
				return GLFW_KEY_5;
			case Keyboard::Key::Num6:
				return GLFW_KEY_6;
			case Keyboard::Key::Num7:
				return GLFW_KEY_7;
			case Keyboard::Key::Num8:
				return GLFW_KEY_8;
			case Keyboard::Key::Num9:
				return GLFW_KEY_9;
			case Keyboard::Key::Esc:
				return GLFW_KEY_ESCAPE;
			case Keyboard::Key::Enter:
				return GLFW_KEY_ENTER;
			case Keyboard::Key::LShift:
				return GLFW_KEY_LEFT_SHIFT;
			case Keyboard::Key::RShift:
				return GLFW_KEY_RIGHT_SHIFT;
			case Keyboard::Key::LAlt:
				return GLFW_KEY_LEFT_ALT;
			case Keyboard::Key::RAlt:
				return GLFW_KEY_RIGHT_ALT;
			default:
				return GLFW_KEY_0;
				break;
			}
		}
	};
}

#endif /* __MB_KEYBOARD__ */