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

#include "Helpers.hpp"
#include "io/Input.hpp"
#include "scene/Node.hpp"
#include <iostream>

namespace mb
{
  ChangeTransformationComponent::ChangeTransformationComponent( void )
     : mb::Component()
  {
  }
  void ChangeTransformationComponent::start( void )
  {
	  _moveComp = getNode()->getComponent<mb::MoveComponent>();
	  _rotateComp = getNode()->getComponent<mb::RotateComponent>();
  }
  void ChangeTransformationComponent::fixedUpdate(const float&)
  {
    if (mb::Input::isKeyClicked(mb::Keyboard::Key::X))
    {
		_rotateComp->setAxis(mb::Axis::x);
    }
    else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Y))
    {
		_rotateComp->setAxis(mb::Axis::y);
    }
    else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Z))
    {
		_rotateComp->setAxis(mb::Axis::z);
    }
    if (mb::Input::isKeyClicked(mb::Keyboard::Key::P))
    {
		_moveComp->toggle();
    }
  }
  PointMaterial::PointMaterial( void )
    : Material()
  {
    _uniforms["projection"] = new Uniform(Matrix4);
    _uniforms["view"] = new Uniform(Matrix4);
    _uniforms["model"] = new Uniform(Matrix4);
    _uniforms["color"] = new Uniform(Vector3, Vect3(1.0f, 1.0f, 1.0f));
    _uniforms["size"] = new Uniform(Float, 1.0f);
    _uniforms["sizeAttenuation"] = new Uniform(Boolean, false);
    _uniforms["opacity"] = new Uniform(Float, 1.0f);

    const char* vsShader = R"(#version 330
      layout(location = 0) in vec3 position;
      uniform mat4 projection;
      uniform mat4 view;
      uniform mat4 model;
      uniform float size;
      uniform bool sizeAttenuation;
      void main( )
      {
        vec4 pointPosition = view * model * vec4(position, 1.0);
        if (sizeAttenuation)
        {
          gl_PointSize = size * (scale / length(pointPosition.xyz));
        }
        else
        {
          gl_PointSize = size;
        }
        gl_Position = projection * pointPosition;
      })";
    const char* fsShader = R"(#version 330
      out vec4 fragColor;
      uniform float opacity;
      uniform vec3 color;
      void main( )
      {
        fragColor = vec4(color, opacity);
      })";
    _program->loadFromText(vsShader, fsShader);
    _program->compileAndLink();
    _program->autocatching();

    /*
      fragColor = fragColor * texture( tex,
          vec2( gl_PointCoord.x, 1.0 - gl_PointCoord.y ) );
      fragColor.a = opacity;
    */

    // TODO: Enable blending
    // blend_src_rgb = SRC_ALPHA
  }
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
  RotateComponent::RotateComponent(Axis axis, float velocity, bool rotate)
    : mb::Component()
    , _rotate(rotate)
    , _axis(axis)
    , _delta(0.01f)
    , _velocity(velocity)
  {
  }
#ifdef MB_USE_RAPIDJSON
  RotateComponent::RotateComponent(const rapidjson::Value& config)
  : RotateComponent(_axisFromString(config["axis"].GetString( )))
  {
    if (config.HasMember("rotate"))
    {
      bool rotate = config["rotate"].GetBool();
      setRotate(rotate);
    }
  }
#endif
  Axis RotateComponent::_axisFromString(const std::string& _axis_)
  {
    if (_axis_ == "X")
    {
      return mb::Axis::x;
    } else if (_axis_ == "Y")
    {
      return mb::Axis::y;
    } else if (_axis_ == "Z")
    {
      return mb::Axis::z;
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
      }
    }
  }
  ScaleComponent::ScaleComponent( void )
    : mb::Component()
    , _inc(0.0f)
  {
  }
  void ScaleComponent::update(const float& /*dt*/)
  {
    this->_node->transform().scale().set(
      this->_inc * 0.01,
      this->_inc * 0.01,
      this->_inc * 0.01
    );
    this->_inc += 1.0f;
  }
  PrintPosition::PrintPosition( void )
    : mb::Component()
  {
  }
  void PrintPosition::fixedUpdate(const float&)
  {
    mb::Vect3 pos = this->_node->transform().position();
    std::cout << "POSITION: " << pos.x() << ", " << pos.y() << ", "
      << pos.z() << std::endl;
  }
}
