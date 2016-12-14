/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 *      <https://github.com/maldicion069/monkeybrushplusplus>
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
#include <ctime>

mb::ScenePtr scene;

void renderFunc( float dt );

float mathRandom()
{
  return ((float)rand() / (RAND_MAX));
}

void randomCube(mb::NodePtr node)
{
  float size = std::ceil( mathRandom( ) * 3.0f );
  mb::DrawablePtr model = std::make_shared<mb::Cube>( 1.0f * size );

  mb::SimpleShadingMaterialPtr material = std::make_shared<mb::SimpleShadingMaterial>( );

  material->uniform( "color" )->value( mb::Vect3(
    mb::Color3::createFromHex( mathRandom( ) * 0xffffff ) ) );

  // Add cube
  mb::NodePtr mbNode = std::make_shared<mb::Node>( std::string( "cube-" + std::to_string( scene->root( )->getNumChildren( ) ) ) );
  mbNode->addComponent( std::make_shared<mb::MeshRenderer>( model, material ) );

  mbNode->transform( ).position( ).x( -15.0f + std::round( ( mathRandom( ) * 50.0f ) ) );
  mbNode->transform( ).position( ).y( std::round( mathRandom( ) * 5.0f ) );
  mbNode->transform( ).position( ).z( -10.0f + std::round( mathRandom( ) * 50.0f ) );

  node->addChild( mbNode );
}

int main( void )
{
  srand( ( unsigned int ) time( nullptr ) );

  mb::GLContext context( 4, 4, 1024, 768, "Random cubes" );

  auto engine = std::make_shared<mb::Engine>( &context, false );
  scene = std::make_shared<mb::Scene>( engine,
    new mb::SimpleCamera( mb::Vect3( 0.2f, 0.18f, 8.44f ) ) );

  for ( unsigned int i = 0; i < 150; ++i )
  {
    randomCube( scene->root( ) );
  }

  engine->run( renderFunc );

  return 0;
}

float rotSpeed = 0.25f;

void renderFunc( float dt )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  /*scene->root( )->traverse( [=]( mb::NodePtr n )
  {
    if ( n->getMesh( ) != nullptr )
    {
      n->transform( ).rotation( ).x( n->transform( ).rotation( ).x( ) + rotSpeed * dt );
      n->transform( ).rotation( ).y( n->transform( ).rotation( ).y( ) + rotSpeed * dt );
      n->transform( ).rotation( ).z( n->transform( ).rotation( ).z( ) + rotSpeed * dt );
    }
  });*/

  if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Minus ) )
  {
    // Rem cube
    unsigned int maxCubes = scene->root( )->getNumChildren( );
    std::cout << "Total: " << maxCubes << std::endl;
    if ( maxCubes > 1 )
    {
      scene->root( )->removeChild( 0u );
    }
  }
  if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Plus ) )
  {
    randomCube( scene->root( ) );
  }
  scene->render( dt );
}
