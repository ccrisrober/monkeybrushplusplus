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

class HeightMapController : public mb::Component
{
public:
  HeightMapController( const float& amount )
    : mb::Component( )
    , _amount( amount ) {}
  virtual void fixedUpdate( const float& ) override
  {
    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Plus ) )
    {
      _amount -= 0.1f;
      getNode( )->getMesh( )->getMaterial( )->uniform( "amount" )->value( _amount );
    }
    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Minus ) )
    {
      _amount += 0.1f;
      getNode( )->getMesh( )->getMaterial( )->uniform( "amount" )->value( _amount );
    }
  }
protected:
  float _amount;
};

class HeightmapMaterial : public mb::Material
{
public:
  HeightmapMaterial( const float& amount = 5.0f )
      : mb::Material( )
  {
    _uniforms[ "projection" ] = new mb::Uniform( mb::Matrix4 );
    _uniforms[ "view" ] = new mb::Uniform( mb::Matrix4 );
    _uniforms[ "model" ] = new mb::Uniform( mb::Matrix4 );
    _uniforms[ "amount" ] = new mb::Uniform( mb::Float, amount );
    _uniforms[ "tex" ] = new mb::Uniform( mb::TextureSampler, nullptr );

    const char* vsShader = R"(#version 330
      layout(location = 0) in vec3 position;
      layout(location = 1) in vec3 normal;
      layout(location = 2) in vec2 uv;

      out vec2 outUV;

      uniform mat4 projection;
      uniform mat4 view;
      uniform mat4 model;
      uniform float amount;
      uniform sampler2D tex;
      void main( void )
      {
        mat3 normalMatrix = mat3(inverse(transpose(model)));
        vec3 pos = position;
        outUV = uv;
        const vec2 size = vec2(0.5, 0.0);
        const ivec3 off = ivec3(-1, 0, 1);
        vec4 wave = texture(tex, outUV);
        float s11 = wave.x;
        float s01 = textureOffset(tex, outUV, off.xy).x;
        float s21 = textureOffset(tex, outUV, off.zy).x;
        float s10 = textureOffset(tex, outUV, off.yx).x;
        float s12 = textureOffset(tex, outUV, off.yz).x;
        vec3 va = normalize(vec3(size.xy, s21 - s01));
        vec3 vb = normalize(vec3(size.yx, s12 - s10));
        vec4 bump = vec4(cross(va, vb), s11);
        pos.y += amount * bump.w;
        vec4 pp = model * vec4(pos, 1.0);
        pp = view * pp;
        gl_Position = projection * pp;
      })";
    const char* fsShader = R"(#version 330
      in vec2 outUV;
      uniform sampler2D tex;
      out vec4 fragColor;
      void main( void )
      {
        fragColor = texture(tex, outUV);
      };)";
    _program->loadFromText( vsShader, fsShader );
    _program->compileAndLink( );
    _program->autocatching( );

    Cull = false;
  }
};

void renderFunc( float dt );

void loadResources( void )
{
  mb::TexOptions opts;
  opts.minFilter = mb::ctes::TextureFilter::Nearest;
  opts.magFilter = mb::ctes::TextureFilter::Nearest;
  opts.wrapS = mb::ctes::WrapMode::Clamp2Edge;
  opts.wrapT = mb::ctes::WrapMode::Clamp2Edge;
  mb::TexturePtr tex = std::make_shared<mb::Texture2D>( opts,
    MB_TEXTURE_ASSETS + std::string( "/heightmap.jpg" ) );
  mb::TextureCache::add( "heightmapTex", tex );
}

int main( void )
{
  mb::GLContext context( 3, 3, 1024, 768, "Heightmap" );

  auto engine = std::make_shared<mb::Engine>( &context, false );
  scene = std::make_shared<mb::Scene>( engine,
    new mb::SimpleCamera( mb::Vect3( -0.6f, 5.0f, 14.8f ) ) );

  float amount = 5.0f;
  mb::NodePtr mbNode = std::make_shared<mb::Node>( std::string( "model" ) );
  mb::DrawablePtr plane = std::make_shared<mb::Plane>( 26.0f, 20.0f, 200, 200 );
  mbNode->addComponent( std::make_shared<mb::MeshRenderer>( plane,
    std::make_shared<HeightmapMaterial>( amount ) ) );
  mbNode->addComponent( std::make_shared<HeightMapController>( amount ) );

  scene->root( )->addChild( mbNode );

  loadResources( );

  mbNode->getMesh( )->getMaterial( )->uniform( "tex" )->value(
    mb::TextureCache::get( "heightmapTex" ) );

  engine->run( renderFunc );

  return 0;
}

void renderFunc( float dt )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  scene->render( dt );
}
