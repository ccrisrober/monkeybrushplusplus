/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 * <https://github.com/maldicion069/monkeybrushplusplus>
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
#include "../io/Input.hpp"
#include <string>
#include "../materials/Material.hpp"

#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

void _check_gl_error(const char *file, int line)
{
  GLenum err(glGetError());

  if (err != GL_NO_ERROR)
  {
    std::string error;

    switch (err)
    {
      case GL_INVALID_OPERATION:
        error = "INVALID_OPERATION";
        break;
      case GL_INVALID_ENUM:
        error = "INVALID_ENUM";
        break;
      case GL_INVALID_VALUE:
        error = "INVALID_VALUE";
        break;
      case GL_OUT_OF_MEMORY:
        error = "OUT_OF_MEMORY";
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        error = "INVALID_FRAMEBUFFER_OPERATION";  break;
    }

    std::cerr << "GL_" << error.c_str() << " - "
      << file << ":" << line << std::endl;
    err = glGetError();
  }
}

namespace mb
{
  Engine::Engine(GLContext* context, bool debugLayer)
  : _context(context)
  , deltaTime(0.0f)
  , lastFrame(0.0f)
  , _debugLayer(debugLayer)
  {
    mb::LOG(mb::LOG::INFO) << "Initializing Engine";
    Input::initialize();

    Material::_context = context;

    this->state()->color.setClear(mb::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    this->state()->setViewport(mb::Vect4(
      0, 0,
      this->_context->getWidth(), this->_context->getHeight()));

    this->state()->depth.setStatus(true);
    this->state()->culling.setStatus(true);

    mb::LOG(mb::LOG::INFO) << "Engine initialized";
  }
  void Engine::run(std::function<void(float)> loop)
  {
    float currentFrame;

    do
    {

      if (mb::Input::isKeyPressed(mb::Keyboard::Key::Esc))
      {
        break;
      }

      this->_context->setTitle(std::to_string(calcFPS()).c_str(), true);

      currentFrame = glfwGetTime();
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;
      loop(deltaTime);

      if (_debugLayer == true)
      {
        check_gl_error();
      }

      this->_context->getWindow()->swapBuffers();

      this->_context->getWindow()->pollEvents();

      mb::Input::update();
    } while (this->_context->getWindow()->isRunning());
  }
  void Engine::close()
  {
    this->_context->close();
  }
  void Engine::setViewport(const Vect4& vp)
  {
    this->_context->state()->setViewport(vp);
  }
  GlobalState * Engine::state()
  {
    return this->_context->state();
  }
  GLContext* Engine::context()
  {
    return this->_context;
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
