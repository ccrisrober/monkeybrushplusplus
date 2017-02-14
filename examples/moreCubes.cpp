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

int main(void)
{
  mb::GLContext context( 3, 3, 1024, 768, "Hello MonkeyBrush" );

  auto engine = std::make_shared<mb::Engine>( &context, false );
  scene = std::make_shared<mb::Scene>( engine,
    new mb::SimpleCamera( mb::Vect3( 0.2f, 0.18f, 25.0f ) ) );

  mb::DrawablePtr mesh = std::make_shared<mb::Cube>( 5.0f );

  mb::SimpleShadingMaterialPtr material = std::make_shared<mb::SimpleShadingMaterial>( );
  material->uniform( "color" )->value( mb::Vect3( mb::Color3::Blue ) );
  material->Cull = false;
  //material->PolygonMode = GL_LINE;

  mb::NodePtr mbNode = std::make_shared<mb::Node>( std::string( "mesh" ) );
  mbNode->addComponent( std::make_shared<mb::MeshRenderer>( mesh, material ) );

  std::cout << mbNode->getComponent<mb::MeshRenderer>()->getComponentName( ) << std::endl;

  //mbNode->addComponent( std::make_shared<mb::MoveComponent>( ) );
  //mbNode->addComponent(std::make_shared<mb::RotateComponent>(mb::Axis::x, 0.5f, true));
  //mbNode->addComponent(std::make_shared<mb::RotateComponent>(mb::Axis::y, 0.1f, true));

  mb::DrawablePtr geom2 = std::make_shared<mb::Cube>(0.5f);
  mb::SimpleShadingMaterialPtr material2 = std::make_shared<mb::SimpleShadingMaterial>( );
  material2->uniform("color")->value(mb::Vect3(mb::Color3::Red));
  /*const int max = 10;
  for ( int i = -max; i < max; ++i)
  {
    for ( int j = -max; j < max; ++j)
    {
  	  mb::NodePtr mbNode_ = std::make_shared<mb::Node>(std::string("mesh"));
  	  mbNode_->transform( ).position( ).x( i );
  	  mbNode_->transform( ).position( ).y( j );
  	  mbNode_->addComponent(std::make_shared<mb::MeshRenderer>(geom2, material2));
      mbNode->addChild( mbNode_ );
    }
  }*/

  scene->root( )->addChild( mbNode );

  engine->run( renderFunc );

  return 0;
}

void renderFunc( float dt )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //mesh.rotation.x += 0.005;
  //mesh.rotation.y += 0.001;
  scene->render( dt );
}
