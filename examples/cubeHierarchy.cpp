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

mb::Scene* scene;

void renderFunc(float dt);

float myrand()
{
  return ((float)rand() / (RAND_MAX)) + 1.0f;
}
mb::Node* group;
int main(void)
{
  mb::GLContext context(3, 3, 1024, 768, "Cube Hierarchy");

  auto engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine, new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 10.5f)));

	mb::Drawable* model = new mb::Cube(0.25f);

  mb::NormalMaterial material;

	group = new mb::Node(std::string("MyGroup"));

  for (unsigned int i = 0; i < 150; ++i)
  {
    auto mbMesh = new mb::Node(std::string("cube-") + std::to_string(i));
    mbMesh->addComponent(mb::ComponentPtr(new mb::MeshRenderer(model, &material)));

    float positionx = myrand() * 2.0f - 1.0f;
    float positiony = myrand() * 2.0f - 1.0f;
    float positionz = myrand() * 2.0f - 1.0f;

    float rotationx = myrand() * 2.0f * mb::Mathf::PI;
    float rotationy = myrand() * 2.0f * mb::Mathf::PI;

    mbMesh->transform().position().set(positionx, positiony, positionz);
    mbMesh->transform().rotation().x(rotationx);
    mbMesh->transform().rotation().y(rotationy);
    group->addChild(mb::NodePtr(mbMesh));
  }

	/*mbNode-
  mbNode->addComponent(mb::ComponentPtr(new mb::ChangeTransformationComponent()));
	mbNode->addComponent(mb::ComponentPtr(new mb::MoveComponent()));*/

	scene->root()->addChild(mb::NodePtr(group));

	engine->run(renderFunc);

	// delete(scene);
	delete(engine);

  return 0;
}

float globalTime = 0.0f;

void renderFunc(float dt)
{
  globalTime += dt;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  float rx = std::sin(globalTime * 0.7f) * 0.5f,
    ry = std::sin(globalTime * 0.3f) * 0.5f,
    rz = std::sin(globalTime * 0.2f) * 0.5f;

  group->transform().rotation().set(rx, ry, rz);

	scene->render(dt);
}
