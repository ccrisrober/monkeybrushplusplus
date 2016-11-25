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

#include "Window.hpp"
#include "Input2.hpp"

namespace MB
{
	bool GLFWWindow2::init()
	{
		if (!glfwInit())
		{
			throw "Failed to initialise GLFW";
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _params.minVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _params.maxVersion);
		glfwWindowHint(GLFW_SAMPLES, 4);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// TODO: glfwWindowHint(GLFW_RESIZABLE, _params.resizable);



		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);



		glfwWindowHint(GLFW_RESIZABLE, false);

		std::cout << "OpenGL context version: (" << _params.minVersion << ", " << _params.maxVersion << ")" << std::endl;

		this->_handle = glfwCreateWindow(_params.width, _params.height, _params.title, nullptr, nullptr);

		if (_handle == nullptr)
		{
			glfwTerminate();
			throw "Failed to create window with GLFW.";
		}

		glfwSetInputMode(_handle, GLFW_STICKY_KEYS, GL_TRUE);
		glfwMakeContextCurrent(_handle);

		// Initialize GLEW to setup the OpenGL Function pointers
		glewExperimental = (GLboolean)true;
		if (glewInit() != GLEW_OK)
		{
			glfwTerminate();
			throw "Failed to initialise GLEW";
		}

		glfwSetKeyCallback(_handle, [](GLFWwindow*, int key, int, int action, int)
		{
			if (action == GLFW_PRESS)
			{
				static_cast<GLFWKeyboard*>(Input2::Keyboard())->onKeyDown(key);
			}
			else if (action == GLFW_RELEASE)
			{
				static_cast<GLFWKeyboard*>(Input2::Keyboard())->onKeyUp(key);
			}
		});

		glfwSetCursorPosCallback(_handle, [](GLFWwindow*, double xpos, double ypos)
		{
			static_cast<GLFWMouse*>(Input2::Mouse())->onMouseMove(static_cast<int>(xpos), static_cast<int>(ypos));
		});

		glfwSetMouseButtonCallback(_handle, [](GLFWwindow*, int button, int action, int)
		{
			static_cast<GLFWMouse*>(Input2::Mouse())->onMouseButtonEvent(button, action);
		});

		glfwSetScrollCallback(_handle, [](GLFWwindow*, double xoffset, double yoffset)
		{
			static_cast<GLFWMouse*>(Input2::Mouse())->onMouseWheelEvent(static_cast<int>(xoffset), static_cast<int>(yoffset));
		});

		return true;
	}
}
