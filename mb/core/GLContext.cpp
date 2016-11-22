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

#include "GLContext.hpp"

#include "../Includes.hpp"

#include "Input.hpp"
#include <functional>

namespace MB
{
    GLContext::GLContext(unsigned int minVersion, unsigned int maxVersion,
                         unsigned int width, unsigned int height,
                         const char* title)
		: _minVersion(minVersion)
		, _maxVersion(maxVersion)
        , _width(width)
        , _height(height)
        , _title(title)
    {
        if (!glfwInit())
        {
            throw "Failed to initialise GLFW";
        }
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, maxVersion);
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		std::cout << "OpenGL context version: (" << minVersion << ", " << maxVersion << ")" << std::endl;

        this->_window = glfwCreateWindow(_width, _height, title, nullptr, nullptr);

        if (_window == nullptr)
	    {
            glfwTerminate();
            throw "Failed to create window with GLFW.";
	    }


		//glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
		glfwMakeContextCurrent(_window);

        // Initialize GLEW to setup the OpenGL Function pointers
        glewExperimental = (GLboolean) true;
        if (glewInit() != GLEW_OK)
        {
            glfwTerminate();
            throw "Failed to initialise GLEW";
        }

		Input::init();

		_state = new GlobalState();

		/*std::function<void(GLFWwindow*, int, int, int)> mouseCallback([=](GLFWwindow*, int button, int action, int) {
		});
		std::function<void(GLFWwindow*, double, double)> scrollCallback([=](GLFWwindow*, double xoff, double yoff) {
		});
		std::function<void(GLFWwindow*, int, int, int, int)> keyCallback([=](GLFWwindow*, int key, int, int action, int) {
		});*/
		glfwSetKeyCallback(getWindow(), &key_callback);
		glfwSetMouseButtonCallback(getWindow(), &mouse_button_callback);
	}
	GLFWwindow* GLContext::getWindow() const
	{
		return this->_window;
	}
}
