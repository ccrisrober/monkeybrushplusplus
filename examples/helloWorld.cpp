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

mb::Engine* engine;
mb::Scene* scene;

void renderFunc(float dt);

typedef mb::RotateComponent* RC;

mb::Node* mbModel;

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Hello mb");

    engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::Polyhedron* model = new mb::Tetrahedron(1.0f, 2);

	mb::SimpleShadingMaterial material;
	material.uniform("color")->value(mb::Vect3(mb::Color3::Blue));

	mbModel = new mb::Node(std::string("model"));
	mbModel->setMesh(new mb::MeshRenderer(model, &material));
	mbModel->addComponent(new mb::MoveComponent());
	mbModel->addComponent(new mb::RotateComponent(mb::Axis::x));

	mbModel->getComponent<mb::RotateComponent>()->setRotate(true);

	//mbModel->disableComponent<mb::RotateComponent>();
	//mbModel->enableComponent<mb::RotateComponent>();
	//mbModel->hasComponent<mb::RotateComponent>();
	
	scene->root()->addChild(mbModel);

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->camera->update(dt);
	if (mb::Input2::isKeyPressed(mb::Keyboard::Key::Esc))
	{
		engine->close();
		return;
	}
	if (mb::Input2::isKeyClicked(mb::Keyboard::Key::X))
	{
		mbModel->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::x);
	}
	else if (mb::Input2::isKeyClicked(mb::Keyboard::Key::Y))
	{
		mbModel->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::y);
	}
	else if (mb::Input2::isKeyClicked(mb::Keyboard::Key::Z))
	{
		mbModel->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::z);
	}
	if (mb::Input2::isKeyClicked(mb::Keyboard::Key::P))
	{
		mbModel->toggleComponent<mb::MoveComponent>();
	}
	engine->state()->culling.setStatus(false);
	engine->state()->setPolygonMode(GL_LINE);
	scene->render(dt);
}
