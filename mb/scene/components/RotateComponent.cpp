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

#include "RotateComponent.hpp"

#include "../../io/Input.hpp"
#include "../Node.hpp"

namespace mb
{
  RotateComponent::RotateComponent(mb::Vect3 axis, float velocity, bool rotate)
    : mb::Component()
    , _rotate(rotate)
    , _axis(axis)
    , _delta(0.01f)
    , _velocity(velocity)
  {
  }
  RotateComponent::RotateComponent(const std::string& axisName,
    float velocity, bool rotate)
    : RotateComponent(_axisFromString( axisName), velocity, rotate)
  {
  }
  mb::Vect3 RotateComponent::_axisFromString(std::string _axis_)
  {
  _axis_ = StringUtils::toUpper(_axis_);
    if (_axis_ == "X")
    {
      return mb::Vect3::xAxis;
    } else if (_axis_ == "Y")
  {
    return mb::Vect3::yAxis;
    } else if (_axis_ == "Z")
  {
    return mb::Vect3::zAxis;
  }
  else if (_axis_ == "XY")
  {
    return mb::Vect3(1.0f, 1.0f, 0.0f);
  }
  else if (_axis_ == "XZ")
  {
    return mb::Vect3(1.0f, 0.0f, 1.0f);
  }
  else if (_axis_ == "YZ")
  {
    return mb::Vect3(0.0f, 1.0f, 1.0f);
  }
  else if (_axis_ == "XYZ")
  {
    return mb::Vect3(1.0f, 1.0f, 1.0f);
  }
    throw;
  }
  void RotateComponent::update(const float& dt)
  {
    if (mb::Input::isKeyClicked(mb::Keyboard::Key::Space))
    {
      this->_rotate = !this->_rotate;
    }
    if (this->_rotate)
    {
      this->_delta += this->_velocity * dt;
    this->_node->transform().rotation().x(_axis.x() * this->_delta);
    this->_node->transform().rotation().y(_axis.y() * this->_delta);
    this->_node->transform().rotation().z(_axis.z() * this->_delta);
    /**
      switch (_axis)
      {
      case Axis::x:
        this->_node->transform().rotation().x(this->_delta);
        break;
      case Axis::y:
        this->_node->transform().rotation().y(this->_delta);
        break;
      case Axis::z:
        this->_node->transform().rotation().z(this->_delta);
        break;
      }*/
    }
  }
}
