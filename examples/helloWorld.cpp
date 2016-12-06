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

mb::Node* mbModel;

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Hello MonkeyBrush");

    engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::Drawable* model = new mb::Tetrahedron(1.0f, 2);

	mb::SimpleShadingMaterial material;
	material.uniform("color")->value(mb::Vect3(mb::Color3::Blue));
	material.Cull = false;
	material.PolygonMode = GL_LINE;

	mbModel = new mb::Node(std::string("model"));
	mbModel->setMesh(new mb::MeshRenderer(model, &material));
	mbModel->addComponent(new mb::MoveComponent());
	mbModel->addComponent(new mb::RotateComponent(mb::Axis::x, 0.25f, true));

	scene->root()->addChild(mbModel);

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->mainCamera->update(dt);
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::X))
	{
		mbModel->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::x);
	}
	else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Y))
	{
		mbModel->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::y);
	}
	else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Z))
	{
		mbModel->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::z);
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::P))
	{
		mbModel->toggleComponent<mb::MoveComponent>();
	}
	scene->render(dt);
}
