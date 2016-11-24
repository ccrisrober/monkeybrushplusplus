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

#include "Input2.hpp"

namespace MB
{
	void Input2::initialize()
	{
		Input2* _instance = Input2::instance();

		_instance->_keyboard = new GLFWKeyboard();
		_instance->_mouse = new GLFWMouse();
	}
	void Input2::destroy()
	{
		Input2* _instance = Input2::instance();
		delete _instance->_mouse;
		delete _instance->_keyboard;
		delete _instance;
	}
	MB::Keyboard* Input2::Keyboard()
	{
		auto input = Input2::instance();
		return input->_keyboard;
	}
	MB::Mouse* Input2::Mouse()
	{
		auto input = Input2::instance();
		return input->_mouse;
	}
	bool Input2::isKeyPressed(Keyboard::Key key)
	{
		auto input = Input2::instance();
		return input->_keyboard->keyPress(key);
	}
	bool Input2::isKeyClicked(Keyboard::Key key)
	{
		auto input = Input2::instance();
		return input->_keyboard->singleKeyPress(key);
	}
	bool Input2::KeyReleased(Keyboard::Key key)
	{
		auto input = Input2::instance();
		return input->_keyboard->keyRelease(key);
	}
	int Input2::MouseX()
	{
		auto input = Input2::instance();
		return input->_mouse->mouseX();
	}
	int Input2::MouseY()
	{
		auto input = Input2::instance();
		return input->_mouse->mouseY();
	}
	Input2* Input2::instance()
	{
		if (!Input2::_instance)
		{
			Input2::_instance = new MB::Input2();
		}
		return Input2::_instance;
	}
	int Input2::PreviousMouseX()
	{
		auto input = Input2::instance();
		return input->_mouse->previousMouseX();
	}
	int Input2::PreviousMouseY()
	{
		auto input = Input2::instance();
		return input->_mouse->previousMouseY();
	}
	int Input2::MouseWheelX()
	{
		auto input = Input2::instance();
		return input->_mouse->mouseWheelX();
	}
	int Input2::MouseWheelY()
	{
		auto input = Input2::instance();
		return input->_mouse->mouseWheelY();
	}
	int Input2::DeltaX(int val)
	{
		auto input = Input2::instance();
		return input->_mouse->deltaX(val);
	}
	int Input2::DeltaY(int val)
	{
		auto input = Input2::instance();
		return input->_mouse->deltaY(val);
	}
	bool Input2::MouseButtonPress(MouseButton button)
	{
		auto input = Input2::instance();
		return input->_mouse->buttonPress(button);
	}
	bool Input2::MouseButtonSinglePress(MouseButton button)
	{
		auto input = Input2::instance();
		return input->_mouse->singleButtonPress(button);
	}
	bool Input2::MouseButtonRelease(MouseButton button)
	{
		auto input = Input2::instance();
		return input->_mouse->buttonRelease(button);
	}
	void Input2::update()
	{
		Input2* _instance = Input2::instance();
		_instance->_keyboard->update();
		_instance->_mouse->update();
	}
	Input2* Input2::_instance = nullptr;
}
