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

#include <iostream>
#include <mb/mb.h>
#include <assetsFiles.h>

mb::ScenePtr scene;

void renderFunc( float dt );

int main(void)
{
  mb::GLContext context( 3, 3, 1024, 768, "Alpha Textures" );

  auto engine = std::make_shared<mb::Engine>( &context, false );
  scene = std::make_shared<mb::Scene>( engine,
    new mb::SimpleCamera( mb::Vect3( 0.2f, 0.18f, 8.44f ) ) );

  mb::DrawablePtr mesh = std::make_shared<mb::Cube>( 2.0f );

  std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
    {
      mb::VertexShader,
      "#version 330\n"
      "layout(location = 0) in vec3 position;\n"
      "layout(location = 2) in vec2 uv;\n"
      "out vec2 outUV;\n"
      "uniform mat4 projection;\n"
      "uniform mat4 view;\n"
      "uniform mat4 model;\n"
      "void main( void ) {\n"
      " gl_Position = projection * view * model * vec4(position, 1.0);\n"
      " outUV = uv;\n"
      "}"
    },{
      mb::FragmentShader,
      "#version 330\n"
      "out vec4 fragColor;\n"
      "in vec2 outUV;\n"
      "uniform sampler2D alphaTex;\n"
      "uniform sampler2D diffTex;\n"
      "void main( void ) {\n"
      " vec4 T0 = texture(alphaTex, outUV);\n"
      " vec4 T1 = texture(diffTex, outUV);\n"
      " fragColor = mix(T1, T0, T0.a);\n"
      "}\n"
    }
  };

  mb::TexOptions opts;
  mb::TexturePtr tex1 = std::make_shared<mb::Texture2D>( opts, MB_TEXTURE_ASSETS + std::string( "/fragile.png" ) );
  mb::TexturePtr tex2 = std::make_shared<mb::Texture2D>( opts, MB_TEXTURE_ASSETS + std::string( "/woodenBox.png" ) );

  std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
    std::make_pair( "projection", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "view", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "model", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "viewPos", new mb::Uniform( mb::Vector3 ) ),
    std::make_pair( "alphaTex", new mb::Uniform( mb::TextureSampler, tex1 ) ),
    std::make_pair( "diffTex", new mb::Uniform( mb::TextureSampler, tex2 ) ),
  };

  auto material = std::make_shared<mb::ShaderMaterial>( "material", shaders, uniforms );

  auto mbModel = std::make_shared<mb::Node>( std::string( "model" ) );
  mbModel->addComponent( std::make_shared<mb::MeshRenderer>( mesh, material ) );
  mbModel->addComponent( std::make_shared<mb::RotateComponent>( mb::Axis::y, 0.35f ) );

  mbModel->getComponent<mb::RotateComponent>( )->setRotate( true );

  scene->root( )->addChild( mbModel );

  engine->run( renderFunc );

  return 0;
}

void renderFunc( float dt )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  scene->render( dt );
}
