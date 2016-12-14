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

#include <iostream>
#include <mb/mb.h>
#include <assetsFiles.h>
#include <shaderFiles.h>

mb::ScenePtr scene;

void renderFunc( float dt );

mb::ShaderMaterialPtr createMaterial(const std::string sourceName)
{
  std::string vertexShader = mb::os::readFile( MB_SHADER_FILES + std::string( "/" + sourceName + ".vert" ) );
  std::string fragmentShader = mb::os::readFile( MB_SHADER_FILES + std::string( "/" + sourceName + ".frag" ) );

  std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
    {
      mb::VertexShader, vertexShader.c_str( )
    }, {
      mb::FragmentShader, fragmentShader.c_str( )
    }
  };

  std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
    std::make_pair( "projection", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "view", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "model", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "color", new mb::Uniform( mb::Vector3, mb::Vect3( mb::Color3::Green ) ) )
  };
  return std::make_shared<mb::ShaderMaterial>( sourceName, shaders, uniforms );
}

mb::MaterialPtr flatMaterial, smootMaterial, noperspectiveMaterial;

class NormalInterpolationComponent : public mb::Component
{
public:
  virtual void update( const float ) override
  {
    if ( mb::Input::isKeyClicked( mb::Keyboard::Key::Num1 ) )
    {
      this->_node->getMesh( )->setMaterial( mb::MaterialCache::get( std::string( "flatNormal" ) ) );
    }
    else if ( mb::Input::isKeyClicked( mb::Keyboard::Key::Num2 ) )
    {
      this->_node->getMesh( )->setMaterial( mb::MaterialCache::get( std::string( "smoothNormal" ) ) );
    }
    else if ( mb::Input::isKeyClicked( mb::Keyboard::Key::Num3 ) )
    {
      this->_node->getMesh( )->setMaterial( mb::MaterialCache::get( std::string( "noPerspectiveNormal" ) ) );
    }
  }
};

int main( void )
{
  mb::GLContext context( 3, 3, 1024, 768, "Normal interpolation" );

  auto engine = std::make_shared<mb::Engine>( &context, false );
  scene = std::make_shared<mb::Scene>( engine,
    new mb::SimpleCamera( mb::Vect3( 0.2f, 0.18f, 8.44f ) ) );

  mb::DrawablePtr mesh = std::make_shared<mb::Mesh>(
    MB_MODEL_ASSETS + std::string( "/suzanne.obj_" ) );

  flatMaterial = createMaterial( "flatNormal" );
  smootMaterial = createMaterial( "smoothNormal" );
  noperspectiveMaterial = createMaterial( "noPerspectiveNormal" );

  auto mbNode = new mb::Node( std::string( "mesh" ) );
  mbNode->addComponent( mb::ComponentPtr( new mb::MeshRenderer( mesh, flatMaterial ) ) );
  mbNode->addComponent( mb::ComponentPtr( new mb::MoveComponent( ) ) );
  mbNode->addComponent( mb::ComponentPtr( new mb::RotateComponent( mb::Axis::x ) ) );
  mbNode->addComponent( mb::ComponentPtr( new NormalInterpolationComponent( ) ) );
  mbNode->addComponent( mb::ComponentPtr( new mb::ChangeTransformationComponent( ) ) );

  scene->root( )->addChild( mb::NodePtr( mbNode ) );

  engine->run( renderFunc );

  return 0;
}

void renderFunc( float dt )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  scene->render( dt );
}
