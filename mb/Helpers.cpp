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
  ChangeTransformationComponent::ChangeTransformationComponent() 
     : mb::Component()
  {
  }
  void ChangeTransformationComponent::update(const float)
  {
    if (mb::Input::isKeyClicked(mb::Keyboard::Key::X))
    {
      getNode()->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::x);
    }
    else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Y))
    {
      getNode()->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::y);
    }
    else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Z))
    {
      getNode()->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::z);
    }
    if (mb::Input::isKeyClicked(mb::Keyboard::Key::P))
    {
      getNode()->toggleComponent<mb::MoveComponent>();
    }
  }
  PointMaterial::PointMaterial()
    : Material()
  {
    _uniforms["projection"] = new Uniform(Matrix4);
    _uniforms["view"] = new Uniform(Matrix4);
    _uniforms["model"] = new Uniform(Matrix4);
    _uniforms["color"] = new Uniform(Vector3, Vect3(1.0f, 1.0f, 1.0f));
    _uniforms["size"] = new Uniform(Float, 1.0f);
    _uniforms["sizeAttenuation"] = new Uniform(Boolean, false);
    _uniforms["opacity"] = new Uniform(Float, 1.0f);

    const char* vsShader = "#version 330\n"
      "layout(location = 0) in vec3 position;"
      "uniform mat4 projection;"
      "uniform mat4 view;"
      "uniform mat4 model;"
      "uniform float size;"
      "uniform bool sizeAttenuation;"
      "void main() {"
      " vec4 pointPosition = view * model * vec4(position, 1.0);\n"
      " if (sizeAttenuation) \n"
      "   gl_PointSize = size * (scale / length(pointPosition.xyz));\n"
      " else\n"
      "   gl_PointSize = size;\n"
      "    gl_Position = projection * pointPosition;\n"
      "}";
    const char* fsShader = "#version 330\n"
      "out vec4 fragColor;\n"
      "uniform float opacity;\n"
      "uniform vec3 color;\n"
      "void main() {\n"
      " fragColor = vec4(color, opacity);\n"
      "}\n";
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
  MoveComponent::MoveComponent()
    : mb::Component()
    , _delta(0.01f)
    , _sign(1)
    , _velocity(1.0f)
  {
  }
  void MoveComponent::update(const float dt)
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
  void RotateComponent::update(const float dt)
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
  ScaleComponent::ScaleComponent()
    : mb::Component()
    , _inc(0.0f)
  {
  }
  void ScaleComponent::update(float /*dt*/)
  {
    this->_node->transform().scale().set(
      this->_inc * 0.01,
      this->_inc * 0.01,
      this->_inc * 0.01
    );
    this->_inc += 1.0f;
  }
  PrintPosition::PrintPosition()
    : mb::Component()
  {
  }
  void PrintPosition::update(const float)
  {
    mb::Vect3 pos = this->_node->transform().position();
    std::cout << "POSITION: " << pos.x() << ", " << pos.y() << ", "
      << pos.z() << std::endl;
  }
}
