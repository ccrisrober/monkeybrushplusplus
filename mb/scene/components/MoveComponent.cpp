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

#include "MoveComponent.hpp"

#include "../../io/Input.hpp"
#include "../Node.hpp"

namespace mb
{
  MoveComponent::MoveComponent( void )
    : mb::Component()
    , _delta(0.01f)
    , _sign(1)
    , _velocity(1.0f)
  {
  }
  void MoveComponent::update(const float& dt)
  {
    if (mb::Input::isKeyPressed(mb::Keyboard::Key::V))
    {
      this->_velocity -= 0.1f;
      if (this->_velocity < 0.0f) this->_velocity = 0.0f;
    }
    else if (mb::Input::isKeyPressed(mb::Keyboard::Key::B))
    {
      this->_velocity += 0.1f;
      if (this->_velocity > 10.0f) this->_velocity = 10.0f;
    }
    if (this->_delta > 2.5f || this->_delta < -2.5f)
    {
      this->_sign *= -1;
    }
    this->_delta = (this->_delta > 2.5f) ? 2.5f : this->_delta;
    this->_delta = (this->_delta < -2.5f) ? -2.5f : this->_delta;
    this->_delta += this->_velocity * this->_sign * dt;
    this->_node->transform().position().x(this->_delta);
  }
}
