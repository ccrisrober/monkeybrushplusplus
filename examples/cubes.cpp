/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 *    <https://github.com/maldicion069/monkeybrushplusplus>
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

mb::ScenePtr scene;

void renderFunc( float dt );

class Rotate : public mb::Component
{
public:
  Rotate( )
    : mb::Component( )
    , _rotate( false )
    {
    }
  virtual void update( const float dt ) override
  {
    if ( mb::Input::isKeyClicked( mb::Keyboard::Key::Space ) )
    {
      this->_rotate = !this->_rotate;
    }
    if ( this->_rotate)
    {
      auto xRot = _node->transform( ).rotation( ).y( );
      auto yRot = _node->transform( ).rotation( ).y( );
      _node->transform( ).rotation( ).x( xRot + dt );
      _node->transform( ).rotation( ).y( yRot + dt );
      }
    }
protected:
    bool _rotate;
};

int main(void)
{
  mb::GLContext context(3, 3, 1024, 768, "Cubes");

  auto engine = std::make_shared<mb::Engine>( &context, false );
  scene = std::make_shared<mb::Scene>( engine,
    new mb::SimpleCamera( mb::Vect3( 0.2f, 0.18f, 8.44f ) ) );

  mb::DrawablePtr cube = std::make_shared<mb::Cube>(2.0f);

  unsigned int MAX = 5;
  for ( unsigned int zz = 0; zz < MAX; ++zz )
  {
    for ( unsigned int yy = 0; yy < MAX; ++yy )
    {
      for ( unsigned int xx = 0; xx < MAX; ++xx )
      {
        auto mbCube = std::make_shared<mb::Node>( std::string( "cube" ) );

        auto material = std::make_shared<mb::SimpleShadingMaterial>( );
        material->uniform( "color" )->value( mb::Vect3( mb::Color3(
          ( float ) xx / MAX,
          ( float ) yy / MAX,
          ( float ) zz / MAX )
        ) );
        mbCube->addComponents( {
          std::make_shared<mb::MeshRenderer>( cube, material ),
          std::make_shared<Rotate>( ),
        } );
        mbCube->transform( ).position( ).set(
          -15.0f + xx * +6.0f,
          -15.0f + yy * +6.0f,
          zz * 6.0 );
        mbCube->transform( ).rotation( ).y( xx * 0.21f + yy + 0.37f );
        scene->root( )->addChild( mbCube );
      }
    }
  }

  engine->run( renderFunc );

  return 0;
}

void renderFunc( float dt )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    scene->render( dt );
}
