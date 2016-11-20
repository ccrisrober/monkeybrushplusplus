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

#include "Engine.hpp"
#include "../core/Input.hpp"
#include <string>

#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

void _check_gl_error(const char *file, int line)
{
	GLenum err(glGetError());

	if (err != GL_NO_ERROR)
	{
		std::string error;

		switch (err)
		{
			case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
			case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
			case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
			case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
		}

		std::cerr << "GL_" << error.c_str() << " - " << file << ":" << line << std::endl;
		err = glGetError();
	}
}

namespace MB
{
	Engine::Engine(GLContext* context)
	: _context(context)
	, deltaTime(0.0f)
	, lastFrame(0.0f)
	{
		// TODO: INIT Input
	}
	void Engine::run(std::function<void(float)> loop)
	{
		float currentFrame;
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		
		glViewport(0, 0, this->_context->getWidth(), this->_context->getHeight());
		
		glEnable(GL_DEPTH_TEST);

		glDisable(GL_CULL_FACE);
		while (!glfwWindowShouldClose(this->_context->getWindow( )))
        {
            this->_context->setTitle(std::to_string(calcFPS()).c_str(), false);

			glfwPollEvents();

			MB::Input::update();
			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;  
			loop(deltaTime);

			check_gl_error();

	        glfwSwapBuffers(this->_context->getWindow( ));
	    }
	}

    void Engine::close()
    {
        this->_context->close();
    }

	double Engine::calcFPS(double theTimeInterval)
	{
		// Static values which only get initialised the first time the function runs
		static double t0Value       = glfwGetTime(); // Set the initial time to now
		static int    fpsFrameCount = 0;             // Set the initial FPS frame count to 0
		static double fps           = 0.0;           // Set the initial FPS value to 0.0

		// Get the current time in seconds since the program started (non-static, so executed every time)
		currentTime = glfwGetTime();

		// Ensure the time interval between FPS checks is sane (low cap = 0.1s, high-cap = 10.0s)
		// Negative numbers are invalid, 10 fps checks per second at most, 1 every 10 secs at least.
		if (theTimeInterval < 0.1)
		{
			theTimeInterval = 0.1;
		}
		if (theTimeInterval > 10.0)
		{
			theTimeInterval = 10.0;
		}

		// Calculate and display the FPS every specified time interval
		if ((currentTime - t0Value) > theTimeInterval)
		{
			// Calculate the FPS as the number of frames divided by the interval in seconds
			fps = (double)fpsFrameCount / (currentTime - t0Value);

			// Reset the FPS frame counter and set the initial time to be now
			fpsFrameCount = 0;
			t0Value = glfwGetTime();
		}
		else // FPS calculation time interval hasn't elapsed yet? Simply increment the FPS frame counter
		{
			fpsFrameCount++;
		}

		// Return the current FPS - doesn't have to be used if you don't want it!
		return fps;
	}
}
