/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal
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

#ifndef __MB_INPUT__
#define __MB_INPUT__

#include <vector>
#include <GLFW/glfw3.h>

namespace MB {
	class Input {
	public:
		static bool isKeyPressed(int keycode) {
            return _isKeyPressed[keycode];
		}
		static bool isKeyClicked(int keycode) {
            return _isKeyClicked[keycode];
		}
		static bool isButtonPressed(int button) {
			return _isButtonPressed[button];
		}
		static bool isButtonClicked(int button) {
			return _isButtonClicked[button];
		}

		static void update()
		{
			for (unsigned i = 0; i < GLFW_KEY_LAST; ++i)
			{
                _isKeyClicked[i] = (!_keyPreviusState[i]) && _isKeyPressed[i];
                _keyPreviusState[i] = _isKeyPressed[i];
			}
			for (unsigned i = 0; i < 3; ++i)
			{
                _isButtonClicked[i] = (!_buttonPreviousState[i]) && _isButtonPressed[i];
                _buttonPreviousState[i] = _isButtonPressed[i];
			}
		}

		static void init() {
			if(!_initializated)
			{
				_initializated = true;

				_buttonPreviousState.resize(3, false);
				_isButtonPressed.resize(3, false);
				_isButtonClicked.resize(3, false);

				_keyPreviusState.resize(GLFW_KEY_LAST, false);
				_keyPreviusState.resize(GLFW_KEY_LAST, false);
				_isKeyClicked.resize(GLFW_KEY_LAST, false);
			}
		}

	protected:
		static bool _initializated;
		static std::vector<bool> _buttonPreviousState;
		static std::vector<bool> _isButtonPressed;
		static std::vector<bool> _isButtonClicked;
		static std::vector<bool> _keyPreviusState;
		static std::vector<bool> _isKeyPressed;
		static std::vector<bool> _isKeyClicked;
	};
}

#endif /* __MB_INPUT__ */