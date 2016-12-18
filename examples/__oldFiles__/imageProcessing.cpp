/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 * <https://github.com/maldicion069/monkeybrushplusplus>
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
#include <shaderFiles.h>

mb::Scene* scene;

void renderFunc( float dt );

mb::PostProcessMaterial *ppm;

mb::Texture2D *tex;

float amount = 0.5f;

mb::GLContext* context;

mb::RenderTarget *rt;

int main(void)
{
  context = new mb::GLContext(3, 3, 512, 512, "Image Processing");

  mb::TexOptions opts;
  opts.minFilter = mb::ctes::TextureFilter::Nearest;
  opts.magFilter = mb::ctes::TextureFilter::Nearest;
  opts.type = GL_FLOAT;
  opts.format = GL_RGB;
  opts.internalFormat = GL_RGB;

  rt = new mb::RenderTarget(context->getWidth(), context->getHeight(), {
    new mb::Texture2D(opts, context->getWidth(), context->getHeight())
  });

  auto engine = new mb::Engine(context, false);
  scene = new mb::Scene(engine,
    new mb::SimpleCamera(mb::Vect3(0.0f, -0.5f, 10.0f)));

  std::string imageProcessing = mb::os::readFile(MB_SHADER_FILES
    + std::string("/imageProcessing.frag"));
  ppm = new mb::PostProcessMaterial(imageProcessing.c_str( ));

  ppm->addUniform("tex", new mb::Uniform(mb::TextureSampler, rt->textures()[0]));
  ppm->addUniform("mode", new mb::Uniform(mb::Integer, 0));

  mb::Cube* model = new mb::Cube(1.0f);

  int v = 0;
  for (int i = -4; i < 4; ++i)
  {
    //mb::NormalMaterial* material = new mb::NormalMaterial();
    mb::SimpleShadingMaterial* material = new mb::SimpleShadingMaterial();
    mb::Color3 cc;
    switch (v % 4)
    {
    case 0:
      cc = mb::Color3::Blue;
      break;
    case 1:
      cc = mb::Color3::Red;
      break;
    case 2:
      cc = mb::Color3::Green;
      break;
    case 3:
      cc = mb::Color3::Orange;
      break;
    }
    ++v;
    material->uniform("color")->value(mb::Vect3(cc));
    mb::Node* mbModel = new mb::Node(std::string("model"));
    mbModel->addComponent(mb::ComponentPtr(new mb::MeshRenderer(model, material)));

    /*if (i % 2 == 0)
    {
      mbModel->addComponent(mb::ComponentPtr(new mb::RotateComponent(mb::Axis::x)));
    }
    else
    {
      mbModel->addComponent(mb::ComponentPtr(new mb::RotateComponent(mb::Axis::y)));
    }

    mbModel->getComponent<mb::RotateComponent>()->setRotate(true);*/

    mbModel->transform().position().set(i * 1.0f, i * 1.5f, i * 1.0f);
    //std::cout << mbModel->transform().position().x() << std::endl;
    scene->root( )->addChild(mb::NodePtr(mbModel));
  }

  engine->run(renderFunc);

  //delete(scene);
  delete(engine);

  return 0;
}

void renderFunc( float dt )
{
  if (mb::Input::isKeyPressed(mb::Keyboard::Key::Num0))
  {
    ppm->uniform("mode")->value(0);
    context->setTitle("Image Processing - No effect");
  }
  if (mb::Input::isKeyPressed(mb::Keyboard::Key::Num1))
  {
    ppm->uniform("mode")->value(1);
    context->setTitle("Image Processing - Blur");
  }
  if (mb::Input::isKeyPressed(mb::Keyboard::Key::Num2))
  {
    ppm->uniform("mode")->value(2);
    context->setTitle("Image Processing - Sharpen");
  }
  if (mb::Input::isKeyPressed(mb::Keyboard::Key::Num3))
  {
    ppm->uniform("mode")->value(3);
    context->setTitle("Image Processing - Edge");
  }
  if (mb::Input::isKeyPressed(mb::Keyboard::Key::Num4))
  {
    ppm->uniform("mode")->value(4);
    context->setTitle("Image Processing - Emboss");
  }
  if (mb::Input::isKeyPressed(mb::Keyboard::Key::Num5))
  {
    ppm->uniform("mode")->value(5);
    context->setTitle("Image Processing - Grayscale");
  }
  if (mb::Input::isKeyPressed(mb::Keyboard::Key::Num6))
  {
    ppm->uniform("mode")->value(6);
    context->setTitle("Image Processing - Contrast");
  }
  if (mb::Input::isKeyPressed(mb::Keyboard::Key::Num7))
  {
    ppm->uniform("mode")->value(7);
    context->setTitle("Image Processing - Brighten");
  }
  if (mb::Input::isKeyPressed(mb::Keyboard::Key::Num8))
  {
    ppm->uniform("mode")->value(8);
    context->setTitle("Image Processing - Darken");
  }
  if (mb::Input::isKeyPressed(mb::Keyboard::Key::Num9))
  {
    ppm->uniform("mode")->value(9);
    context->setTitle("Image Processing - Sepia");
  }

  rt->bind();
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glEnable(GL_DEPTH_TEST);
  scene->render( dt );
  rt->unbind();
  glClear( GL_COLOR_BUFFER_BIT );
  glDisable(GL_DEPTH_TEST);
  rt->bindTextures();
  ppm->renderPP();
}
