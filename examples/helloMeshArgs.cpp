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
#include <sstream>

mb::Scene* scene;

void renderFunc(float dt);

int main(int argc, char** argv)
{
  mb::ArgumentParser parser = mb::ArgumentParser().description("Draw a mesh!");
  parser.add_option("-f", "--file").dest("filename").help("Mesh import file");
  parser.add_option("-c", "--color").dest("color").help("Mesh color");
  mb::Values opts = parser.parse_args(argc, argv);

  if (!opts.is_set("filename"))
  {
    std::cerr << "Filename undefined" << std::endl;
    parser.print_help();
    exit(-1);
  }

  std::string s = "0xfffefffe";
  if (opts.is_set("color"))
  {
    s = opts.get("color");
  }
  unsigned int hex = std::stoul(s, nullptr, 16);
  
  std::string filename = opts.get("filename");

  mb::GLContext context(3, 3, 1024, 768, "Hello Mesh for arguments");

  auto engine = new mb::Engine(&context, false);
  scene = new mb::Scene(engine, 
    new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 8.44f)));

  mb::Mesh* mesh = new mb::Mesh(filename);

  mb::SimpleShadingMaterial material;
  material.uniform("color")->value(mb::Vect3(mb::Color3::createFromHex(hex)));

  auto mbNode = new mb::Node(std::string("mesh"));
  mbNode->addComponent(mb::ComponentPtr(new mb::MeshRenderer(mesh, &material)));
  mbNode->addComponent(mb::ComponentPtr(new mb::ChangeTransformationComponent()));
  mbNode->addComponent(mb::ComponentPtr(new mb::MoveComponent()));
  mbNode->addComponent(mb::ComponentPtr(
    new mb::RotateComponent(mb::Axis::x, 0.75f, true)));

  scene->root()->addChild(mb::NodePtr(mbNode));

  engine->run(renderFunc);

  //delete(scene);
  delete(engine);

  return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->render(dt);
}
