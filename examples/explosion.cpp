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
#include <vector>

mb::ScenePtr scene;

void renderFunc( float dt );

class ExplosionComponent : public mb::Component
{
public:
  ExplosionComponent( )
    : mb::Component( )
    , _globalTime( 0.0f )
  {}
  virtual void update( const float& dt ) override
  {
    _globalTime += dt;
    getNode( )->getMesh( )->getMaterial( )->uniform( "time" )->value( _globalTime );
  }
protected:
  float _globalTime;
};

int main( void )
{
  mb::GLContext context( 3, 3, 1024, 768, "Model explosion" );

  auto engine = std::make_shared<mb::Engine>( &context, false );
  scene = std::make_shared<mb::Scene>( engine,
    new mb::SimpleCamera( mb::Vect3( 0.2f, 0.18f, 18.44f ) ) );

  std::vector<std::pair<mb::ShaderType, const char*> > shaders;
  const char* vertexShader =
    R"(#version 330 core
    layout(location = 0) in vec3 position;
    layout(location = 2) in vec2 texCoords;
    out VS_OUT
    {
      vec2 texCoords;
    } vs_out;
    uniform mat4 projection;
    uniform mat4 view;
    uniform mat4 model;
    void main( void )
    {
      gl_Position = projection * view * model * vec4(position, 1.0f);
      vs_out.texCoords = texCoords;
    })";
  const char* geometryShader =
    R"(#version 330 core
    layout (triangles) in;
    layout (triangle_strip, max_vertices = 3) out;
    in VS_OUT
    {
      vec2 texCoords;
    } gs_in[];
    out vec2 TexCoords;
    uniform float time;
    vec4 explode(vec4 position, vec3 normal)
    {
      float magnitude = 2.0f;
      vec3 direction = normal * ((sin(time) + 1.0f) / 2.0f) * magnitude;
      return position + vec4(direction, 0.0f);
    }
    vec3 GetNormal()
    {
      vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
      vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
      return normalize(cross(a, b));
    }
    void main( void )
    {
      vec3 normal = GetNormal();
      gl_Position = explode(gl_in[0].gl_Position, normal);
      TexCoords = gs_in[0].texCoords;
      EmitVertex();
      gl_Position = explode(gl_in[1].gl_Position, normal);
      TexCoords = gs_in[1].texCoords;
      EmitVertex();
      gl_Position = explode(gl_in[2].gl_Position, normal);
      TexCoords = gs_in[2].texCoords;
      EmitVertex();
      EndPrimitive();
    })";
  const char* fragmentShader =
    R"(#version 330
    out vec4 fragColor;
    uniform vec3 color;
    void main( void )
    {
      fragColor = vec4(color, 1.0);
    })";

  shaders.push_back( std::make_pair( mb::VertexShader, vertexShader ) );
  shaders.push_back( std::make_pair( mb::GeometryShader, geometryShader ) );
  shaders.push_back( std::make_pair( mb::FragmentShader, fragmentShader ) );

  std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
    std::make_pair( "projection", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "view", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "model", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "color", new mb::Uniform( mb::Vector3, mb::Vect3( 0.0f, 1.0f, 1.0f ) ) ),
    std::make_pair( "time", new mb::Uniform( mb::Float, 0.015f ) )
  };

  mb::ShaderMaterialPtr material = std::make_shared<mb::ShaderMaterial>(
    "geomExplosion", shaders, uniforms );

  mb::DrawablePtr draw1 = std::make_shared<mb::Torus>( 0.5f, 0.25f, 25, 40 );
  mb::DrawablePtr draw2 = std::make_shared<mb::Octahedron>( 0.5f, 2 );
  mb::DrawablePtr draw3 = std::make_shared<mb::Cone>( 0.5f, 0.25f, 1.0f, 25, 25 );

  mb::NodePtr mbObj = std::make_shared<mb::Node>( std::string( "model" ) );
  mbObj->addComponent( std::make_shared<mb::MeshRenderer>( draw1, material ) );
  mbObj->addComponent( std::make_shared<mb::MoveComponent>( ) );
  mbObj->addComponent( std::make_shared<mb::RotateComponent>( mb::Axis::x ) );
  mbObj->addComponent( std::make_shared<ExplosionComponent>( ) );
  mbObj->transform( ).position( ).y( 3.5f );
  mbObj->transform( ).rotation( ).y( -1.44f );

  mb::NodePtr mbObj2 = std::make_shared<mb::Node>( std::string( "model-2" ) );
  mbObj2->addComponent( std::make_shared<mb::MeshRenderer>( draw2, material ) );
  mbObj2->addComponent( std::make_shared<mb::MoveComponent>( ) );
  mbObj2->addComponent( std::make_shared<mb::RotateComponent>( mb::Axis::x ) );
  mbObj2->addComponent( std::make_shared<ExplosionComponent>( ) );
  mbObj2->transform( ).position( ).y( 0.0f );

  mb::NodePtr mbObj3 = std::make_shared<mb::Node>( std::string( "model-3" ) );
  mbObj3->addComponent( std::make_shared<mb::MeshRenderer>( draw3, material ) );
  mbObj3->addComponent( std::make_shared<mb::MoveComponent>( ) );
  mbObj3->addComponent( std::make_shared<mb::RotateComponent>( mb::Axis::x ) );
  mbObj3->addComponent( std::make_shared<ExplosionComponent>( ) );
  mbObj3->transform( ).position( ).y( -3.5f );
  mbObj3->transform( ).rotation( ).x( 1.44f / 2.0f );

  scene->root( )->addChild( mbObj );
  scene->root( )->addChild( mbObj2 );
  scene->root( )->addChild( mbObj3 );

  engine->run( renderFunc );

  return 0;
}
void renderFunc( float dt )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  scene->render( dt );
}
