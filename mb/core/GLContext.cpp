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

#include <functional>
#include "../resources/ResourceShader.hpp"

namespace mb
{
    GLContext::GLContext(unsigned int maxVersion, unsigned int minVersion,
                         unsigned int width, unsigned int height,
                         const char* title)
		: _minVersion(minVersion)
		, _maxVersion(maxVersion)
        , _width(width)
        , _height(height)
        , _title(title)
    {
		mb::WindowParams wp(width, height);
		wp.title = title;
		wp.minVersion = minVersion;
		wp.maxVersion = maxVersion;
		_window = new mb::GLFWWindow2(wp);
		_window->init();
		
		_state = new GlobalState();
	}
	Window* GLContext::getWindow() const
	{
		return this->_window;
	}
	void GLContext::close()
	{
		//glfwSetWindowShouldClose(_window, GLFW_TRUE);
		//glfwTerminate();
	}
	void GLContext::setTitle(const char* title, bool fullName)
	{
		if (fullName)
		{
			_window->setTitle((std::string(_title) + std::string(" - ") + std::string(title)).c_str());
		}
		else
		{
			_window->setTitle(title);
		}
	}
	unsigned int GLContext::getWidth() const
	{
		return this->_width;
	}
	unsigned int GLContext::getHeight() const
	{
		return this->_height;
	}
	GlobalState* GLContext::state()
	{
		return this->_state;
	}
}
