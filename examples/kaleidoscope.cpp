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
#include <shaderFiles.h>

mb::ScenePtr scene;

void renderFunc( float dt );

mb::PostProcessMaterial* ppm;

float sides, angle;

int main(void)
{
  mb::GLContext context(3, 3, 1024, 768, "Kaleidoscope demo");

  auto engine = std::make_shared<mb::Engine>( &context, false );
  scene = std::make_shared<mb::Scene>(engine,
    new mb::SimpleCamera( mb::Vect3( 0.2f, 0.18f, 8.44f ) ) );

  std::string kaleidoscope = mb::os::readFile( MB_SHADER_FILES + std::string( "/kaleidoscope.frag" ) );

  ppm = new mb::PostProcessMaterial( kaleidoscope.c_str( ) );

  sides = 5.0f;
  angle = 121.0f;

  mb::TexOptions opts;
  opts.wrapS = mb::ctes::WrapMode::MirroredRepeat;
  opts.wrapT = mb::ctes::WrapMode::MirroredRepeat;
  mb::TexturePtr tex = std::make_shared<mb::Texture2D>( opts, MB_TEXTURE_ASSETS + std::string( "/Dundus_Square.jpg" ) );

  ppm->addUniform("iGlobalTime", new mb::Uniform(mb::Float, 0.0f));
  ppm->addUniform("sides", new mb::Uniform(mb::Float, sides));
  ppm->addUniform("angle", new mb::Uniform(mb::Float, angle));
  ppm->addUniform( "tex", new mb::Uniform( mb::TextureSampler, tex ) );

  engine->run(renderFunc);

  return 0;
}

bool play = true;

float globalTime = 0.0f;
void renderFunc( float dt )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  if (mb::Input::isKeyClicked(mb::Keyboard::Key::Space))
  {
    play = !play;
  }
  if (play)
  {
    globalTime += dt * 0.33f;
  }
  ppm->uniform("iGlobalTime")->value(globalTime);
  if (mb::Input::isKeyClicked(mb::Keyboard::Key::Z))
  {
    sides -= 1.0f;
    ppm->uniform("sides")->value(sides);
  }
  else if (mb::Input::isKeyClicked(mb::Keyboard::Key::X))
  {
    sides += 1.0f;
    ppm->uniform("sides")->value(sides);
  }
  if (mb::Input::isKeyClicked(mb::Keyboard::Key::A))
  {
    angle -= 1.0f;
    ppm->uniform("angle")->value(angle);
  }
  else if (mb::Input::isKeyClicked(mb::Keyboard::Key::S))
  {
    angle += 1.0f;
    ppm->uniform("angle")->value(angle);
  }
  ppm->renderPP();
}
