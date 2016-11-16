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

#ifndef __MB_GLCONTEXT__
#define __MB_GLCONTEXT__

#include "../Includes.hpp"
#include "Input.hpp"

namespace MB
{
	class GLContext
	{
	public:
        GLContext(unsigned int minVersion = 3, unsigned int maxVersion = 3,
                  unsigned int width = 500, unsigned int height = 500,
                  const char* title = "Hello MB");
		GLFWwindow* getWindow() const;
        void close( ) {
            glfwTerminate();
        }
        void setTitle(const char* title, bool fullName = true)
        {
            if (fullName)
            {
                glfwSetWindowTitle(_window, (std::string(_title) + std::string(" - ") + std::string(title)).c_str());
            }
            else
            {
                glfwSetWindowTitle(_window, title);
            }
        }
        unsigned int getWidth() const
        {
            return this->_width;
        }
        unsigned int getHeight() const
        {
            return this->_height;
        }

	private:
		static void mouse_button_callback(GLFWwindow*, int /*button*/, int /*action*/, int)
		{
			//if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		}
		static void key_callback(GLFWwindow*, int key, int, int action, int)
		{
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				Input::_onKeyDown(key);
			}
			else if (action == GLFW_RELEASE)
			{
				Input::_onKeyUp(key);
			}
			
		}
	protected:
        unsigned int _minVersion;
        unsigned int _maxVersion;
        unsigned int _width;
        unsigned int _height;
		GLFWwindow* _window;
        std::string _title;
	};
}

#endif /* __MB_GLCONTEXT__ */
