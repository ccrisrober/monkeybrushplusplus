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
#include <random>

mb::ScenePtr scene;

void renderFunc( float dt );

class BrownianMovement: public mb::Component
{
public:
  BrownianMovement( )
    : mb::Component( )
    , _generator( std::default_random_engine( 0 ) )
    , _distribution( std::normal_distribution<float>( 0.0f, 1.0f ) )
	{
	}
	virtual void start()
	{
    _xPos = _node->transform( ).position( ).x( );
    _yPos = _node->transform( ).position( ).y( );
	}
	virtual void update( const float dt ) override
	{
    float i = _xPos + ( _distribution( _generator ) * 5.0f * dt );
    float j = _yPos + ( _distribution( _generator ) * 5.0f * dt );
    float k = ( _distribution( _generator ) * 5.0f * dt );

    _node->transform( ).position( ).set( i, j, k );
	}
protected:
	std::default_random_engine _generator;
	std::normal_distribution<float> _distribution;

  float _xPos;
  float _yPos;
};

void addModel(const float& px, const float& py, const mb::DrawablePtr& mesh,
  const mb::MaterialPtr& material)
{
  mb::NodePtr mbNode = std::make_shared<mb::Node>( std::string( "model" ) );
  mbNode->transform( ).position( ).set( px, py, 0.0f );
  mbNode->addComponent( std::make_shared<mb::MeshRenderer>( mesh, material ) );
  mbNode->addComponent( std::make_shared<BrownianMovement>( ) );

  scene->root( )->addChild( mbNode );
}

int main(void)
{
  mb::GLContext context( 3, 3, 1024, 768, "Brownian Motion" );

  auto engine = std::make_shared<mb::Engine>( &context, false );
  scene = std::make_shared<mb::Scene>( engine,
    new mb::SimpleCamera( mb::Vect3( 0.0f, -2.16f, 22.25f ) ) );

  mb::DrawablePtr cube = std::make_shared<mb::Tetrahedron>( 1.0f, 2 );

  mb::MaterialPtr material = std::make_shared<mb::NormalMaterial>( );

  addModel( -7.5f, -3.5f, cube, material );
  addModel( 0.0f, 3.0f, cube, material );
  addModel( 7.5f, -3.5f, cube, material );
  addModel( 0.0f, -7.5f, cube, material );

  engine->run( renderFunc );

  return 0;
}

void renderFunc( float dt )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	scene->render( dt );
}
