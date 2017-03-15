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

#ifndef __MB_MOVE_COMPONENT__
#define __MB_MOVE_COMPONENT__

#include <mb/api.h>

#include "Component.hpp"

namespace mb
{
  class MoveComponent : public mb::Component
  {
  public:
    MB_API
    static std::shared_ptr<mb::MoveComponent> create( )
    {
      return std::make_shared<mb::MoveComponent>( );
    }
    MB_API
    MoveComponent( void );
    MB_API
    virtual void update( const mb::Clock& clock ) override;
  protected:
    float _delta;
    int _sign;
    float _velocity;
  };
};

#endif /* __MB_MOVE_COMPONENT__ */
