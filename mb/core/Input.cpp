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

#include "Input.hpp"

namespace MB
{
	bool Input::_initializated = false;

	std::vector<bool> Input::_buttonPreviousState;
	std::vector<bool> Input::_isButtonPressed;
	std::vector<bool> Input::_isButtonClicked;
	std::vector<bool> Input::_keyPreviusState;
	std::vector<bool> Input::_isKeyPressed;
	std::vector<bool> Input::_isKeyClicked;

	bool Input::isKeyPressed(int keycode)
	{
        return _isKeyPressed[keycode];
	}
	bool Input::isKeyClicked(int keycode)
	{
        return _isKeyClicked[keycode];
	}
	bool Input::isButtonPressed(int button)
	{
		return _isButtonPressed[button];
	}
	bool Input::isButtonClicked(int button)
	{
		return _isButtonClicked[button];
	}
	void Input::update()
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
	void Input::init()
	{
		if(!_initializated)
		{
			_initializated = true;

			_buttonPreviousState.resize(3, false);
			_isButtonPressed.resize(3, false);
			_isButtonClicked.resize(3, false);

			_keyPreviusState.resize(GLFW_KEY_LAST, false);
			_isKeyPressed.resize(GLFW_KEY_LAST, false);
			_isKeyClicked.resize(GLFW_KEY_LAST, false);
		}
	}
	void Input::_onKeyUp(unsigned int keycode)
	{
		_isKeyPressed[keycode] = false;
	}
	void Input::_onKeyDown(unsigned int keycode)
	{
		_isKeyPressed[keycode] = true;
	}
}
