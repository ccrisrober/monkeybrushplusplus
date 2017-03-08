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
    /*if (mb::Input::isKeyClicked(mb::Keyboard::Key::X))
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
    }*/
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



}
