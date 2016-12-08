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

#include "Mouse.hpp"

using mb::ctes::MouseButton;

#define MOUSE_LEFTBUTTON 0
#define MOUSE_CENTERBUTTON 1
#define MOUSE_RIGHTBUTTON 2

namespace mb
{
  Mouse::~Mouse() {}
  GLFWMouse::GLFWMouse()
    : Mouse()
    , _x(0)
    , _y(0)
    , _prevX(0)
    , _prevY(0)
    , _wheelX(0)
    , _wheelY(0)
    , _prevWheelX(0)
    , _prevWheelY(0)
  {
    _current[MOUSE_LEFTBUTTON].state = GLFW_RELEASE;
    _current[MOUSE_CENTERBUTTON].state = GLFW_RELEASE;
    _current[MOUSE_RIGHTBUTTON].state = GLFW_RELEASE;

    _previous[MOUSE_LEFTBUTTON].state = GLFW_RELEASE;
    _previous[MOUSE_CENTERBUTTON].state = GLFW_RELEASE;
    _previous[MOUSE_RIGHTBUTTON].state = GLFW_RELEASE;
  }
  GLFWMouse::~GLFWMouse() {}
  int GLFWMouse::mouseX()
  {
    return _x;
  }
  int GLFWMouse::mouseY()
  {
    return _y;
  }
  int GLFWMouse::previousMouseX()
  {
    return _prevX;
  }
  int GLFWMouse::previousMouseY()
  {
    return _prevY;
  }
  int GLFWMouse::mouseWheelX()
  {
    return _wheelX;
  }
  int GLFWMouse::mouseWheelY()
  {
    return _wheelY;
  }
  int GLFWMouse::deltaX(int val)
  {
    if (_x != _prevX)
    {
      return _x - val;
    }
    return 0;
  }
  int GLFWMouse::deltaY(int val)
  {
    if (_y != _prevY)
    {
      return _y - val;
    }
    return 0;
  }
  bool GLFWMouse::buttonRelease(MouseButton button)
  {
    switch (button)
    {
    case MouseButton::Left:
      return _current[MOUSE_LEFTBUTTON].state == GLFW_RELEASE && _previous[MOUSE_LEFTBUTTON].state == GLFW_PRESS;
    case MouseButton::Middle:
      return _current[MOUSE_CENTERBUTTON].state == GLFW_RELEASE && _previous[MOUSE_CENTERBUTTON].state == GLFW_PRESS;
    case MouseButton::Right:
      return _current[MOUSE_RIGHTBUTTON].state == GLFW_RELEASE && _previous[MOUSE_RIGHTBUTTON].state == GLFW_PRESS;
    default:
      return false;
    }
  }
  bool GLFWMouse::buttonPress(MouseButton button)
  {
    switch (button)
    {
    case MouseButton::Left:
      return _current[MOUSE_LEFTBUTTON].state == GLFW_PRESS;
    case MouseButton::Middle:
      return _current[MOUSE_CENTERBUTTON].state == GLFW_PRESS;
    case MouseButton::Right:
      return _current[MOUSE_RIGHTBUTTON].state == GLFW_PRESS;
    default:
      return false;
    }
  }
  bool GLFWMouse::singleButtonPress(MouseButton button)
  {
    switch (button)
    {
    case MouseButton::Left:
      return _current[MOUSE_LEFTBUTTON].state == GLFW_PRESS && _previous[MOUSE_LEFTBUTTON].state == GLFW_RELEASE;
    case MouseButton::Middle:
      return _current[MOUSE_CENTERBUTTON].state == GLFW_PRESS && _previous[MOUSE_CENTERBUTTON].state == GLFW_RELEASE;
    case MouseButton::Right:
      return _current[MOUSE_RIGHTBUTTON].state == GLFW_PRESS && _previous[MOUSE_RIGHTBUTTON].state == GLFW_RELEASE;
    default:
      return false;
    }
  }
  void GLFWMouse::update()
  {
    _prevWheelX = _wheelX;
    _prevWheelY = _wheelY;
    _prevX = _x;
    _prevY = _y;
    _wheelY = 0;
    std::memcpy(_previous, _current, sizeof(_current));
  }

  void GLFWMouse::onMouseMove(int x, int y)
  {
    _x = x;
    _y = y;
  }

  void GLFWMouse::onMouseButtonEvent(int e, int action)
  {
    switch (e)
    {
      case GLFW_MOUSE_BUTTON_LEFT:
        _current[MOUSE_LEFTBUTTON].state = static_cast<uint8_t>(action);
        _current[MOUSE_LEFTBUTTON].clicks = 1;
        break;
      case GLFW_MOUSE_BUTTON_MIDDLE:
        _current[MOUSE_CENTERBUTTON].state = static_cast<uint8_t>(action);
        _current[MOUSE_CENTERBUTTON].clicks = 1;
        break;
      case GLFW_MOUSE_BUTTON_RIGHT:
        _current[MOUSE_RIGHTBUTTON].state = static_cast<uint8_t>(action);
        _current[MOUSE_RIGHTBUTTON].clicks = 1;
      break;
    }
  }

  void GLFWMouse::onMouseWheelEvent(int xoffset, int yoffset)
  {
    _wheelX = xoffset;
    _wheelY = yoffset;
  }
}
