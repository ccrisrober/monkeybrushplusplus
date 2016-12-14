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

class ChangeToonLevel : public mb::Component
{
public:
  ChangeToonLevel( const float& level )
    : mb::Component( )
    , _level( level )
  {}
  virtual void update( const float ) override
  {
    if ( mb::Input::isKeyClicked( mb::Keyboard::Key::Plus ) )
    {
      _level += 1.0f;
      getNode( )->getMesh( )->getMaterial( )->uniform( "levels" )->value( _level );
    }
    if ( mb::Input::isKeyClicked( mb::Keyboard::Key::Minus ) )
    {
      _level -= 1.0f;
      if ( _level < 1.0f )
      {
        _level = 1.0f;
      }
      getNode( )->getMesh( )->getMaterial( )->uniform( "levels" )->value( _level );
    }
  }
protected:
  float _level;
};

int main(void)
{
  mb::GLContext context( 3, 3, 1024, 768, "Toon shading" );

  mb::EnginePtr engine = std::make_shared<mb::Engine>( &context, false );
  scene = std::make_shared<mb::Scene>( engine,
    new mb::SimpleCamera( mb::Vect3( 0.2f, 0.18f, 8.44f ) ) );

  mb::DrawablePtr model = std::make_shared<mb::Mesh>(
    MB_MODEL_ASSETS + std::string( "/suzanne.obj_" ) );

	std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
		{
			mb::VertexShader,
      R"(
  			#version 330
  			layout(location = 0) in vec3 position;
  			layout(location = 1) in vec3 normal;
  			out vec3 outPosition;
  			out vec3 outNormal;
  			uniform mat4 projection;
  			uniform mat4 view;
  			uniform mat4 model;
  			void main( void )
        {
          outPosition = vec3(model * vec4(position, 1.0));
          gl_Position = projection * view * vec4(outPosition, 1.0);
          mat3 normalMatrix = mat3(inverse(transpose(model)));
          outNormal = normalize(normalMatrix * normal);
  			}
      )"
		},{
			mb::FragmentShader,
      R"(
        #version 330
        in vec3 outPosition;
        in vec3 outNormal;
        out vec4 fragColor;
        uniform sampler2D tex;
        uniform vec3 viewPos;
        uniform vec3 color;
        uniform float levels;
        void main( void )
        {
            float scaleFactor = 1.0 / levels;
            vec3 n = normalize(outNormal);
          vec3 s = normalize(viewPos.xyz - outPosition.xyz);
            vec3 ambient = color * vec3(0.135, 0.2225, 0.1575);
            float cosine = dot(s, n);
            vec3 diffuse = color * floor(cosine * levels) * scaleFactor;
            fragColor = vec4(vec3(ambient + diffuse), 1.0);
        }
      )"
		}
	};

  float levels = 5.0f;

  std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
    std::make_pair( "projection", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "view", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "model", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "viewPos", new mb::Uniform( mb::Vector3 ) ),
    std::make_pair( "levels", new mb::Uniform( mb::Float, levels ) ),
    std::make_pair( "color", new mb::Uniform( mb::Vector3, mb::Vect3( 0.54f, 0.89f, 0.63f ) ) )
  };

  mb::ShaderMaterialPtr material = std::make_shared<mb::ShaderMaterial>(
    "toonShading", shaders, uniforms );

  mb::NodePtr mbNode = std::make_shared<mb::Node>( std::string( "model" ) );
  mbNode->addComponent( std::make_shared<mb::MeshRenderer>( model, material ) );
  mbNode->addComponent( std::make_shared<mb::RotateComponent>( mb::Axis::y, 0.15f ) );
  mbNode->addComponent( std::make_shared<mb::ChangeTransformationComponent>( ) );
  mbNode->addComponent( std::make_shared<ChangeToonLevel>( levels ) );

  mbNode->getComponent<mb::RotateComponent>( )->setRotate( true );

	scene->root( )->addChild( mbNode );

  engine->run( renderFunc );

	return 0;
}

void renderFunc( float dt )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	scene->render( dt );
}
