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
#include <assetsFiles.h>
#include <shaderFiles.h>

mb::ScenePtr scene;

void renderFunc( float dt );

class ChangeTessLevelComponent : public mb::Component
{
public:
  ChangeTessLevelComponent( const float& tessLevel, const float& tessAlpha )
    : mb::Component( )
    , _innerTessLevel( tessLevel )
    , _outerTessLevel( tessLevel )
    , _tessAlpha( tessAlpha )
  { }
  virtual void fixedUpdate( const float& ) override
  {
    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::H ) )
    {
      _innerTessLevel += 0.1f;
      getNode( )->getMesh( )->getMaterial( )->uniform( "inner_tess_level" )->value( _innerTessLevel );
    }
    else if ( mb::Input::isKeyPressed( mb::Keyboard::Key::G ) )
    {
      _innerTessLevel -= 0.1f;
      if ( _innerTessLevel < 1.0f )
      {
        _innerTessLevel = 1.0f;
      }
      getNode( )->getMesh( )->getMaterial( )->uniform( "inner_tess_level" )->value( _innerTessLevel );
    }
    else if ( mb::Input::isKeyPressed( mb::Keyboard::Key::K ) )
    {
      _outerTessLevel += 0.1f;
      getNode( )->getMesh( )->getMaterial( )->uniform( "outer_tess_level" )->value( _outerTessLevel );
    }
    else if ( mb::Input::isKeyPressed( mb::Keyboard::Key::J ) )
    {
      _outerTessLevel -= 0.1f;
      if ( _outerTessLevel < 1.0f )
      {
        _outerTessLevel = 1.0f;
      }
      getNode( )->getMesh( )->getMaterial( )->uniform( "outer_tess_level" )->value( _outerTessLevel );
    }
    else if ( mb::Input::isKeyPressed( mb::Keyboard::Key::U ) )
    {
      _tessAlpha += 0.1f;
      if ( _tessAlpha > 1.0f )
      {
        _tessAlpha = 1.0f;
      }
      getNode( )->getMesh( )->getMaterial( )->uniform( "tessAlpha" )->value( _tessAlpha );
    }
    else if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Y ) )
    {
      _tessAlpha -= 0.1f;
      if ( _tessAlpha < 0.0f )
      {
        _tessAlpha = 0.0f;
      }
      getNode( )->getMesh( )->getMaterial( )->uniform( "tessAlpha" )->value( _tessAlpha );
    }
  }
protected:
  float _innerTessLevel;
  float _outerTessLevel;
  float _tessAlpha;
};

int main(void)
{
  mb::GLContext context( 4, 4, 1024, 768, "Phong tesselation" );

  mb::EnginePtr engine = std::make_shared<mb::Engine>( &context, false );
  scene = std::make_shared<mb::Scene>( engine,
    new mb::SimpleCamera( mb::Vect3( 0.2f, 0.18f, 8.44f ) ) );

  mb::DrawablePtr model = std::make_shared<mb::Mesh>(
    MB_MODEL_ASSETS + std::string( "/suzanne.obj_" ) );

  std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
    {
      mb::VertexShader,
      R"(#version 440
      layout(location = 0) in vec3 position;
      layout(location = 1) in vec3 normal;

      uniform mat4 model;
      out vec3 vNormal;

      void main( void )
      {
        gl_Position = model * vec4(position, 1.0);
        vNormal = normal;
      })"
    },{
      mb::TesselationControlShader,
      R"(#version 440
      layout (vertices = 3) out;

      uniform float inner_tess_level;
      uniform float outer_tess_level;

      #define ID gl_InvocationID

      struct PhongPatch
      {
        float termIJ;
        float termJK;
        float termIK;
      };

      in vec3 vNormal[];

      out vec3 tcNormal[3];
      out PhongPatch tcPhongPatch[3];

      #define Pi  gl_in[0].gl_Position.xyz
      #define Pj  gl_in[1].gl_Position.xyz
      #define Pk  gl_in[2].gl_Position.xyz

      float PIi(int i, vec3 q)
      {
        vec3 q_minus_p = q - gl_in[i].gl_Position.xyz;
        return q[ID] - dot(q_minus_p, vNormal[i])
                                  * vNormal[i][ID];
      }

      void main( void )
      {
        // get data
        gl_out[ID].gl_Position = gl_in[ID].gl_Position;
        tcNormal[ID] = vNormal[ID];

        // compute patch data
        tcPhongPatch[ID].termIJ = PIi(0,Pj) + PIi(1,Pi);
        tcPhongPatch[ID].termJK = PIi(1,Pk) + PIi(2,Pj);
        tcPhongPatch[ID].termIK = PIi(2,Pi) + PIi(0,Pk);

        // tesselate
        gl_TessLevelOuter[ID] = outer_tess_level;
        gl_TessLevelInner[0] = inner_tess_level;
      })"
    },{
      mb::TesselationEvaluationShader,
      R"(#version 440
      layout(triangles, fractional_odd_spacing, ccw) in;

      struct PhongPatch
      {
        float termIJ;
        float termJK;
        float termIK;
      };

      in vec3 tcNormal[];
      in PhongPatch tcPhongPatch[];

      out vec3 outPosition;
      out vec3 outNormal;

      uniform float tessAlpha;
      uniform mat4 projection;
      uniform mat4 view;

      #define Pi  gl_in[0].gl_Position.xyz
      #define Pj  gl_in[1].gl_Position.xyz
      #define Pk  gl_in[2].gl_Position.xyz
      #define tc1 gl_TessCoord

      void main( void )
      {
        // precompute squared tesscoords
        vec3 tc2 = tc1 * tc1;

        // compute texcoord and normal
        outNormal = gl_TessCoord[0] * tcNormal[0]
                  + gl_TessCoord[1] * tcNormal[1]
                  + gl_TessCoord[2] * tcNormal[2];

        // interpolated position
        vec3 barPos = gl_TessCoord[0] * Pi
                    + gl_TessCoord[1] * Pj
                    + gl_TessCoord[2] * Pk;

        // build terms
        vec3 termIJ = vec3(tcPhongPatch[0].termIJ,
                           tcPhongPatch[1].termIJ,
                           tcPhongPatch[2].termIJ);
        vec3 termJK = vec3(tcPhongPatch[0].termJK,
                           tcPhongPatch[1].termJK,
                           tcPhongPatch[2].termJK);
        vec3 termIK = vec3(tcPhongPatch[0].termIK,
                           tcPhongPatch[1].termIK,
                           tcPhongPatch[2].termIK);

        // phong tesselated pos
        vec3 phongPos = tc2[0] * Pi
                      + tc2[1] * Pj
                      + tc2[2] * Pk
                      + tc1[0] * tc1[1] * termIJ
                      + tc1[1] * tc1[2] * termJK
                      + tc1[2] * tc1[0] * termIK;

        // final position
        vec3 finalPos = mix(barPos, phongPos, tessAlpha);
        outPosition = vec3(view * vec4(finalPos, 1.0));
        gl_Position = projection * vec4(outPosition, 1.0);
      })"
    },{
      mb::FragmentShader,
      R"(#version 440
      in vec3 outPosition;
      in vec3 outNormal;

      uniform vec3 viewPos;
      uniform vec3 color;

      out vec4 fragColor;

      void main( void ) {
        vec3 N = normalize(outNormal);
        vec3 L = normalize(viewPos - outPosition);
        float dif = dot(N, L);
        dif = clamp(dif, 0.0, 1.0);
        fragColor = vec4(color * dif, 1.0) + vec4(color * 0.3, 1.0);
      })"
    }
  };

  float tess_level = 2.0f;
  float tessAlpha = 1.0f;

  std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
    std::make_pair( "projection", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "view", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "model", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "color", new mb::Uniform( mb::Vector3, mb::Vect3( mb::Color3::Brown ) ) ),
    std::make_pair( "inner_tess_level", new mb::Uniform( mb::Float, tess_level ) ),
    std::make_pair( "outer_tess_level", new mb::Uniform( mb::Float, tess_level ) ),
    std::make_pair( "tessAlpha", new mb::Uniform( mb::Float, tessAlpha ) ),
    std::make_pair( "viewPos", new mb::Uniform( mb::Vector3 ) ),
  };

  mb::ShaderMaterialPtr material = std::make_shared<mb::ShaderMaterial>(
    "phongTesselation", shaders, uniforms );
  material->Cull = false;

  mb::NodePtr mbNode = std::make_shared<mb::Node>( std::string( "myTorus" ) );
  mbNode->addComponent( std::make_shared<mb::MeshRendererTesselation>( model, material ) );
  mbNode->addComponent( std::make_shared<ChangeTessLevelComponent>( tess_level, tessAlpha ) );
  scene->root( )->addChild( mbNode );

  engine->run( renderFunc );

  return 0;
}

void renderFunc( float dt )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	scene->render( dt );
}
