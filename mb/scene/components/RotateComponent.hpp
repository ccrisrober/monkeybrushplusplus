/*
* Copyright (c) 2017 maldicion069
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

#ifndef __MB_ROTATE_COMPONENT__
#define __MB_ROTATE_COMPONENT__

#include <mb/api.h>
#include "../../utils/macros.hpp"

#include "Component.hpp"
#include "../../maths/Vect3.hpp"

namespace mb
{
  class RotateComponent : public mb::Component
  {
  public:
    MB_API
    RotateComponent(mb::Vect3 axis,
      float velocity = 1.0f, bool rotate = false);
    MB_API
    RotateComponent(const std::string& axisName,
      float velocity = 1.0f, bool rotate = false);
    MB_API
    virtual void update( const mb::Clock& clock ) override;
    MB_SYNTHESIZE_WRITEONLY(bool, _rotate, Rotate);
    MB_SYNTHESIZE_WRITEONLY(mb::Vect3, _axis, Axis);

  protected:
    mb::Vect3 _axisFromString(std::string axis);
  protected:
    float _delta;
    float _velocity;
  };
};

#endif /* __MB_ROTATE_COMPONENT__ */
