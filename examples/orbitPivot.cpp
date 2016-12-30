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

mb::ScenePtr scene;

class AllRotationComponent : public mb::Component
{
public:
    AllRotationComponent( )
    : mb::Component( )
    { }
    virtual void update( const float& dt ) override
    {
      auto transform = this->_node->transform( );
      float rotX = transform.rotation( ).x( ) + ( speed * dt );
      float rotY = transform.rotation( ).y( ) + ( speed * dt );
      float rotZ = transform.rotation( ).z( ) + ( speed * dt );
      /*std::cout << rotX << ", " << rotY << ", " << rotZ << std::endl;
      transform.rotation().set(
          rotX, rotY, rotZ
      );*/
      this->_node->transform( ).rotation( ).set( rotX, rotY, rotZ );
    }
    float speed = 1.0f;
};

void renderFunc( float dt );

int main(void)
{
  mb::GLContext context( 3, 3, 1024, 768, "Orbit Pivot" );

  auto engine = std::make_shared<mb::Engine>(&context);
  scene = std::make_shared<mb::Scene>( engine,
    new mb::SimpleCamera( mb::Vect3( 2.8f, 1.44f, 43.15f ) ) );

  mb::SimpleShadingMaterialPtr material = std::make_shared<mb::SimpleShadingMaterial>( );
  material->uniform( "color" )->value( mb::Vect3( mb::Color3::Blue ) );
  //material->Cull = false;
  //material->PolygonMode = GL_LINE;

  mb::SimpleShadingMaterialPtr material2 = std::make_shared<mb::SimpleShadingMaterial>( );
  material2->uniform( "color" )->value( mb::Vect3( mb::Color3::Red ) );
  //material2->Cull = false;
  //material2->PolygonMode = GL_LINE;

  mb::DrawablePtr model = std::make_shared<mb::Octahedron>( 7.5f, 1 );
  mb::DrawablePtr model2 = std::make_shared<mb::Torus>( 4.0f );

  mb::NodePtr innerNode = std::make_shared<mb::Node>( "innerNode" );
  innerNode->transform( ).position( ).set( 0.0f, 1.0f, 0.0f );
  innerNode->addComponent( std::make_shared<mb::MeshRenderer>( model, material ) );
  scene->root( )->addChild( innerNode );

  mb::NodePtr pivot = std::make_shared<mb::Node>( "pivot" );
  innerNode->addChild( pivot );
  mb::NodePtr outerNode = std::make_shared<mb::Node>( "outerNode" );
  outerNode->transform( ).position( ).set( 14.0f, 4.0f, 6.0f );

  outerNode->addComponent( std::make_shared<mb::MeshRenderer>( model2, material2 ) );
  pivot->addChild( outerNode );
  pivot->addComponent( std::make_shared<AllRotationComponent>( ) );

  engine->run( renderFunc );

  return 0;
}

void renderFunc( float dt )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  scene->render( dt );
}
