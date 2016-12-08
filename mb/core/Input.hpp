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

#ifndef __MB_INPUT__
#define __MB_INPUT__

#include <mb/api.h>

#include <vector>
#include "../Includes.hpp"

namespace mb
{
  class Input
  {
  public:
    MB_API
    static bool isKeyPressed(int keycode);
    MB_API
    static bool isKeyClicked(int keycode);
    MB_API
    static bool isButtonPressed(int button);
    MB_API
    static bool isButtonClicked(int button);
    MB_API
    static void update();
    MB_API
    static void init();

    MB_API
    static void _onKeyUp(unsigned int keycode);
    MB_API
    static void _onKeyDown(unsigned int keycode);

  protected:
    static bool _initializated;
    static std::vector<bool> _buttonPreviousState;
    static std::vector<bool> _isButtonPressed;
    static std::vector<bool> _isButtonClicked;
    static std::vector<bool> _keyPreviusState;
    static std::vector<bool> _isKeyPressed;
    static std::vector<bool> _isKeyClicked;
  };
}

#endif /* __MB_INPUT__ */
