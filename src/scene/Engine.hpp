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

#ifndef __MB_ENGINE__
#define __MB_ENGINE__

#include <iostream>
#include <functional>
#include "../core/GLContext.hpp"

namespace MB {
	class Engine {
	public:
		Engine(GLContext* context)
		: _context(context)
		, deltaTime(0.0f)
		, lastFrame(0.0f)
		{
			// TODO: INIT Input
		}
		void run(std::function<void(float)> loop)
		{
			float currentFrame;
            //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			while (!glfwWindowShouldClose(this->_context->getWindow( )))
            {
				//float dt = glfwGetTime();
				//dt = calcFPS( );
				currentFrame = glfwGetTime();
				deltaTime = currentFrame - lastFrame;
				lastFrame = currentFrame;  
				loop(deltaTime);
		        glfwSwapBuffers(this->_context->getWindow( ));

		        glfwPollEvents();
		    }
		}

        void close()
        {
            this->_context->close();
        }

    private:
		double calcFPS(double theTimeInterval = 1.0)
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

	protected:
        GLContext* _context;
        float deltaTime;
        float lastFrame;

        double currentTime;
	};
}

#endif /* __MB_ENGINE__ */
