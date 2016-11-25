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

#ifndef __MB_GLCONTEXT__
#define __MB_GLCONTEXT__

#include <mb/api.h>

#include "../Includes.hpp"
#include "GlobalState.hpp"

#include "../io/Window.hpp"

namespace MB
{
	class GLContext
	{
	public:
        MB_API
        GLContext(unsigned int maxVersion = 3, unsigned int minVersion = 3,
                  unsigned int width = 500, unsigned int height = 500,
                  const char* title = "Hello MB");
        MB_API
		Window* getWindow() const;
        MB_API
        void close()
        {
			//glfwSetWindowShouldClose(_window, GLFW_TRUE);
            //glfwTerminate();
        }
        MB_API
        void setTitle(const char* title, bool fullName = true)
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
        MB_API
        unsigned int getWidth() const
        {
            return this->_width;
        }
        MB_API
        unsigned int getHeight() const
        {
            return this->_height;
        }
        MB_API
		GlobalState* state()
		{
			return this->_state;
		}
	protected:
        unsigned int _minVersion;
        unsigned int _maxVersion;
        unsigned int _width;
        unsigned int _height;
		//GLFWwindow* _window;
        std::string _title;

		GlobalState* _state;

		Window* _window;
	};
}

#endif /* __MB_GLCONTEXT__ */
