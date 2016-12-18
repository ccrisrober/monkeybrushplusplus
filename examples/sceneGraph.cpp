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

class ExplosionComponent : public mb::Component
{
public:
  ExplosionComponent( )
    : mb::Component( )
    , _globalTime( 0.0f )
  {
  }
  virtual void update( const float dt ) override
  {
    _globalTime += dt;
    this->_node->getMesh( )->getMaterial( )->uniform( "time" )->value( _globalTime );
  }
protected:
  float _globalTime;
};

int main( void )
{
  mb::GLContext context( 3, 3, 1024, 768, "SceneGraph" );

  auto engine = std::make_shared<mb::Engine>( &context, false );
  scene = std::make_shared<mb::Scene>( engine,
    new mb::SimpleCamera( mb::Vect3( 0.2f, 0.18f, 11.44f ) ) );

  mb::ResourceDrawable::add( "capsule", std::make_shared<mb::Capsule>( 0.5f, 1.0f ) );

  auto cube = std::make_shared<mb::Cube>( 1.0f );
  auto cylinder = std::make_shared<mb::Cylinder>( 1.0f, 1.5f, 25, 15 );
  auto prism = std::make_shared<mb::Prism>( 1.0f, 1.5f, 5 );
  mb::ResourceDrawable::add( "torus", std::make_shared<mb::Torus>( 0.5f, 0.25f, 25, 40 ) );

  mb::SimpleShadingMaterialPtr material = std::make_shared<mb::SimpleShadingMaterial>( );
  material->uniform( "color" )->value( mb::Vect3( mb::Color3::Red ) );
  material->DepthTest = true;

  mb::NormalMaterialPtr normalMat = std::make_shared<mb::NormalMaterial>( );

  std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
    {
      mb::VertexShader,
      R"(
        #version 330
        layout(location = 0) in vec3 position;
        layout(location = 1) in vec3 normal;
        layout(location = 2) in vec2 texCoord;
        out vec3 outPosition;
        out vec3 outNormal;
        out vec2 outTexCoord;
        uniform mat4 projection;
        uniform mat4 view;
        uniform mat4 model;
        void main( void )
        {
          outPosition = vec3(model * vec4(position, 1.0));
          gl_Position = projection * view * vec4(outPosition, 1.0);
          mat3 normalMatrix = mat3(inverse(transpose(model)));
          outNormal = normalize(normalMatrix * normal);
          outTexCoord = texCoord;
        }
      )"
    }, {
      mb::FragmentShader,
      R"(
        #version 330
        in vec3 outPosition;
        in vec3 outNormal;
        in vec2 outTexCoord;
        out vec4 fragColor;
        uniform vec3 viewPos;
        uniform vec3 color;
        void main( void )
        {
          vec3 N = normalize(outNormal);
          vec3 L = normalize(viewPos - outPosition);
          float dif = dot(N, L);
          dif = clamp(dif, 0.0, 1.0);
          fragColor = vec4(color * dif, 1.0) + vec4(color * 0.1, 1.0);
          fragColor.rgb += vec3(outTexCoord, 0.0);
        }
      )"
    }
  };

  std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
    std::make_pair( "projection", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "view", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "model", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "color", new mb::Uniform( mb::Vector3,
        mb::Vect3::createFromScalar( 1.0f ) ) ),
    std::make_pair( "viewPos", new mb::Uniform( mb::Vector3 ) )
  };

  mb::ShaderMaterialPtr shaderMat = std::make_shared<mb::ShaderMaterial>( "shaderMat", shaders, uniforms );
  shaderMat->Cull = false;

  scene->mainCamera->layer( ).enable( 1 );
  scene->mainCamera->layer( ).enable( 2 );
  scene->mainCamera->layer( ).enable( 3 );

  std::vector<std::pair<mb::ShaderType, const char*> > shaders2 = {
    {
      mb::VertexShader,
      R"(
          #version 330 core
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
          }
      )"
    }, {
      mb::GeometryShader,
      R"(
        #version 330 core
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
          float magnitude = 1.0;
          vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude;
          return position + vec4(direction, 0.0);
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
        }
      )"
    }, {
      mb::FragmentShader,
      R"(
        #version 330
        out vec4 fragColor;
        uniform vec3 color;
        void main( void )
        {
          fragColor = vec4(color, 1.0);
        }
      )"
    }
  };

  std::vector<std::pair<const char*, mb::Uniform*> > uniforms2 = {
    std::make_pair( "projection", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "view", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "model", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "color", new mb::Uniform( mb::Vector3, mb::Vect3( mb::Color3::Yellow ) ) ),
    std::make_pair( "time", new mb::Uniform( mb::Float, 0.015f ) )
  };

  mb::ShaderMaterialPtr material2 = std::make_shared<mb::ShaderMaterial>( "geomExplosion", shaders2, uniforms2 );

  mb::NodePtr mbCube = new mb::Node( std::string( "cube" ) );
  mbCube->addComponent( mb::ComponentPtr( std::make_shared<mb::MeshRenderer>( cube, mb::MaterialCache::get( "shaderMat" ) ) ) );
  mbCube->addComponent( mb::ComponentPtr( std::make_shared<mb::MoveComponent>( ) ) );
  mbCube->addComponent( mb::ComponentPtr( std::make_shared<mb::RotateComponent>( mb::Axis::x ) ) );
  mbCube->transform( ).position( ).set( 0.0f, 3.15f, -8.98f );
  mbCube->transform( ).scale( ).set( 2.0f, 2.0f, 1.0f );
  mbCube->layer( ).set( 1 );

  mb::NodePtr mbPrism = std::make_shared<mb::Node>( std::string( "prism" ) );
  mbPrism->addComponent( mb::ComponentPtr( std::make_shared<mb::MeshRenderer>( prism, normalMat ) ) );
  mbPrism->transform( ).position( ).set( -0.44f, -2.0f, 2.35f );
  mbPrism->transform( ).scale( ).set( 0.5f, 0.5f, 1.0f );
  mbCube->addChild( mb::NodePtr( mbPrism ) );
  mbPrism->layer( ).set( 2 );

  mb::NodePtr mbCapsule = std::make_shared<mb::Node>( std::string( "capsule" ) );
  mbCapsule->addComponent( mb::ComponentPtr( std::make_shared<mb::MeshRenderer>( mb::ResourceDrawable::get( "capsule" ), normalMat ) ) );
  mbCapsule->transform( ).position( ).set( -1.44f, -2.5f, 0.87f );
  mbPrism->addChild( mb::NodePtr( mbCapsule ) );
  mbCapsule->layer( ).set( 3 );

  mb::NodePtr mbTorus = std::make_shared<mb::Node>(std::string("torus"));
  mbTorus->addComponent( mb::ComponentPtr( std::make_shared<mb::MeshRenderer>( "torus", material2 ) ) );
  mbTorus->addComponent( mb::ComponentPtr( std::make_shared<ExplosionComponent>( ) ) );
  mbTorus->transform( ).position( ).set( 1.1f, -1.91f, -1.08f );
  mbTorus->transform( ).scale( ).set( 1.0f, 0.5f, 1.0f );
  mbCube->addChild( mb::NodePtr( mbTorus ) );
  mbTorus->layer( ).set( 2 );

  mb::NodePtr mbCylinder = std::make_shared<mb::Node>( std::string( "cylinder" ) );
  mbCylinder->addComponent( mb::ComponentPtr( std::make_shared<mb::MeshRenderer>( cylinder, material ) ) );
  mbCylinder->transform( ).position( ).set( 1.44f, -2.5f, 0.8f );
  mbCylinder->transform( ).scale( ).set( 0.5f, 1.0f, 2.0f );
  mbTorus->addChild( mbCylinder );
  mbCylinder->layer( ).set( 3 );

  std::function<void( )> f0( [&]( )
  {
      std::cout << "SCENE HAS " << scene->root( )->children().size() << " CHILDREN" << std::endl;
  });

  std::function<void( )> f1( [&]( )
  {
    mb::LOG( mb::LOG::INFO ) << "FIRST RENDER FINISHED";
  } );

  std::function<void( )> f2( [&]( )
  {
    std::cout << "MESHES: " << scene->profiler.totalMeshes << ", ";
    std::cout << "VERTICES: " << scene->profiler.totalVertices << ", ";
    std::cout << "INDICES: " << scene->profiler.totalIndices << std::endl;
  });

  scene->registerBeforeRender( f0 );
  scene->registerAfterRender( f1 );
  scene->registerAfterRender( f2, true );

  scene->root( )->addChild( mbCube );

  /*scene->root( )->traverse( []( const mb::NodePtr n )
  {
    std::cout << n->name( ) << std::endl;
  } );*/

  engine->run( renderFunc );

  return 0;
}

void renderFunc( float dt )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  if ( mb::Input::isKeyClicked( mb::Keyboard::Key::Num1 ) )
  {
    scene->mainCamera->layer( ).toggle( 1 );
  }
  if ( mb::Input::isKeyClicked( mb::Keyboard::Key::Num2 ) )
  {
    scene->mainCamera->layer( ).toggle( 2 );
  }
  if ( mb::Input::isKeyClicked( mb::Keyboard::Key::Num3 ) )
  {
    scene->mainCamera->layer( ).toggle( 3 );
  }
  scene->render( dt );
}
