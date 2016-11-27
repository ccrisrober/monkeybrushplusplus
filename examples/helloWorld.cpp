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

MB::Engine* engine;
MB::Scene* scene;

void renderFunc(float dt);

typedef MB::RotateComponent* RC;

MB::Node* mbModel;

int main(void)
{
	MB::GLContext context(3, 3, 1024, 768, "Hello MB");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene(engine);

	MB::Polyhedron* model = new MB::Tetrahedron(1.0f, 2);

	MB::SimpleShadingMaterial material;
	material.uniform("color")->value(MB::Vect3(MB::Color3::Blue));

	mbModel = new MB::Node(std::string("model"));
	mbModel->setMesh(new MB::MeshRenderer(model, &material));
	mbModel->addComponent(new MB::MoveComponent());
	mbModel->addComponent(new MB::RotateComponent(MB::Axis::x));

	mbModel->getComponent<MB::RotateComponent>()->setRotate(true);

	//mbModel->disableComponent<MB::RotateComponent>();
	//mbModel->enableComponent<MB::RotateComponent>();
	//mbModel->hasComponent<MB::RotateComponent>();
	
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
	if (MB::Input2::isKeyPressed(MB::Keyboard::Key::Esc))
	{
		engine->close();
		return;
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::X))
	{
		mbModel->getComponent<MB::RotateComponent>()->setAxis(MB::Axis::x);
	}
	else if (MB::Input2::isKeyClicked(MB::Keyboard::Key::Y))
	{
		mbModel->getComponent<MB::RotateComponent>()->setAxis(MB::Axis::y);
	}
	else if (MB::Input2::isKeyClicked(MB::Keyboard::Key::Z))
	{
		mbModel->getComponent<MB::RotateComponent>()->setAxis(MB::Axis::z);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::P))
	{
		mbModel->toggleComponent<MB::MoveComponent>();
	}
	engine->state()->culling.setStatus(false);
	engine->state()->setPolygonMode(GL_LINE);
	scene->render(dt);
}
