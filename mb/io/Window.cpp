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

#include "Window.hpp"
#include "Input.hpp"
#include <string>

namespace mb
{
  WindowParams::WindowParams( int width_, int height_ )
  {
    this->width = width_;
    this->height = height_;
    this->displayFPS = true;
    this->displayMouse = true;
    this->debugWindowEvents = true;
    this->minVersion = 3;
    this->maxVersion = 3;
    this->resizable = true;
    this->depthBufferBit = 24;
    this->multiSample = 4;
  }
}
