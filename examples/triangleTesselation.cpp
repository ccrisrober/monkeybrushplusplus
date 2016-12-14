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

class ChangeTessLevelComponent : public mb::Component
{
public:
  ChangeTessLevelComponent( const float& tessLevel )
    : mb::Component( )
    , _tessLevel( tessLevel ) { }
  virtual void update( const float ) override
  {
    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Plus ) )
    {
      _tessLevel += 0.1f;
      getNode( )->getMesh( )->getMaterial( )->uniform( "tess_level" )->value( _tessLevel )
    }
    else if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Minus ) )
    {
      _tessLevel -= 0.1f;
      getNode( )->getMesh( )->getMaterial( )->uniform( "tess_level" )->value( _tessLevel );
    }
  }
protected:
  float _tessLevel;
};

int main(void)
{
  mb::GLContext context( 4, 4, 1024, 768, "Triangle tesselation" );

  auto engine = std::make_shared<mb::Engine>( &context, false );
  scene = std::make_shared<mb::Scene>( engine,
    new mb::SimpleCamera( mb::Vect3( 0.2f, 0.18f, 8.44f ) ) );

  mb::DrawablePtr model = std::make_shared<mb::Tetrahedron>( 1.0f );

	std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
		{
			mb::VertexShader,
      R"(
  			#version 440
  			layout(location = 0) in vec3 position;
  			uniform mat4 projection;
  			uniform mat4 view;
  			uniform mat4 model;
  			void main( void )
        {
  			 gl_Position = projection * view * model * vec4(position, 1.0f);
  			}
      )"
		}, {
			mb::TesselationControlShader,
			R"(
      #version 440
  			layout (vertices = 3) out;
  			uniform float tess_level;
        #define ID gl_InvocationID
  			void main(void)
        {
			    if (ID == 0)
          {
		        gl_TessLevelInner[0] = tess_level;
		        gl_TessLevelOuter[0] = tess_level;
		        gl_TessLevelOuter[1] = tess_level;
		        gl_TessLevelOuter[2] = tess_level;
			    }
			    gl_out[ID].gl_Position = gl_in[ID].gl_Position;
  			}
      )"
		}, {
			mb::TesselationEvaluationShader,
      R"(
        #version 440
        layout (triangles) in;
        void main(void)
        {
          gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +
                        (gl_TessCoord.y * gl_in[1].gl_Position) +
                        (gl_TessCoord.z * gl_in[2].gl_Position);
        }
      )"
		}, {
			mb::FragmentShader,
      R"(
        #version 440
        out vec4 fragColor;
        uniform vec3 color;
        void main( void )
        {
          fragColor = vec4(color, 1.0);
        }
      )"
		}
	};

  float tess_level = 2.0f;

  std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
    std::make_pair( "projection", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "view", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "model", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "color", new mb::Uniform( mb::Vector3,
    mb::Vect3( mb::Color3::Pink ) ) ),
    std::make_pair( "tess_level", new mb::Uniform( mb::Float, tess_level ) )
  };

  mb::ShaderMaterialPtr material = std::make_shared<mb::ShaderMaterial>(
    "triangleTesselation", shaders, uniforms );
  material->Cull = false;
  material->PolygonMode = GL_LINE;

  mb::NodePtr mbNode = std::make_shared<mb::Node>( std::string( "model" ) );
	// Same as MeshRenderer(model, &material, GL_PATCHES)
  mbNode->addComponent( std::make_shared<mb::MeshRendererTesselation>( model, material ) );
  mbNode->addComponent( std::make_shared<mb::ChangeTransformationComponent>( ) );
  mbNode->addComponent( std::make_shared<mb::MoveComponent>( ) );
  mbNode->addComponent( std::make_shared<ChangeTessLevelComponent>( tess_level ) );

	scene->root( )->addChild( mbNode );

  engine->run( renderFunc );

  return 0;
}

void renderFunc( float dt )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	scene->render( dt );
}
