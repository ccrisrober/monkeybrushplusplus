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

mb::ScenePtr scene;
mb::RenderTarget *rt;
mb::PostProcessMaterial *ppm;

void renderFunc( float dt );

int main(void)
{
  mb::GLContext context(3, 3, 512, 512, "Sketch Rendering");

  auto engine = std::make_shared<mb::Engine>(&context, false);
  scene = std::make_shared<mb::Scene>(engine,
    new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 8.44f)));

  mb::TexOptions opts;
  opts.minFilter = mb::ctes::TextureFilter::Linear;
  opts.magFilter = mb::ctes::TextureFilter::Nearest;
  opts.type = GL_FLOAT;
  opts.format = GL_RGB;
  opts.internalFormat = GL_RGB;
  opts.wrapS = opts.wrapT = mb::ctes::WrapMode::Clamp2Edge;

  rt = new mb::RenderTarget( context.getWidth( ), context.getHeight( ), {
    std::make_shared<mb::Texture2D>( opts, context.getWidth( ), context.getHeight( ) )
  } );

  mb::DrawablePtr mesh = std::make_shared<mb::Mesh>(
    MB_MODEL_ASSETS + std::string("/suzanne.obj_"));

  mb::NormalMaterialPtr material = std::make_shared<mb::NormalMaterial>();
  ppm = new mb::PostProcessMaterial( R"(
    #version 330
    uniform sampler2D tex;

    out vec4 fragColor;
    in vec2 uv;

    void main()
    {
      fragColor = texture(tex, uv);
      /*fragColor = vec4(uv, 0.0, 1.0);*/
    }
  )");

  ppm->addUniform( "tex", new mb::Uniform( mb::TextureSampler, rt->textures( )[0] ) );

  mb::NodePtr mbNode = std::make_shared<mb::Node>(std::string("mesh"));
  mbNode->addComponents( {
    std::make_shared<mb::MeshRenderer>( mesh, material ),
    std::make_shared<mb::ChangeTransformationComponent>( ),
    std::make_shared<mb::MoveComponent>( ),
    std::make_shared<mb::RotateComponent>( mb::Axis::y, 0.5f, true ),
  } );

  scene->root( )->addChild(mb::NodePtr(mbNode));

  engine->run(renderFunc);

  return 0;
}

void renderFunc( float dt )
{
  rt->bind( );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glEnable( GL_DEPTH_TEST );
  scene->render( dt );
  rt->unbind( );
  glClear( GL_COLOR_BUFFER_BIT );
  glDisable( GL_DEPTH_TEST );
  rt->bindTextures( );
  ppm->renderPP( );
}
