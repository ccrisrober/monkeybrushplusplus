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
#include <random>

MB::Engine* engine;
MB::Scene* scene;

void renderFunc(float dt);

class BrownianMovement: public MB::Component
{
public:
	BrownianMovement()
	: MB::Component()
	, _generator(std::default_random_engine(0))
	, _distribution(std::normal_distribution<float> (0.0f, 1.0f))
	{
	}
	virtual void start()
	{
		_yPos = _node->transform().position().y();
	}
	virtual void update(float dt)
	{
		_node->transform().position().y(_yPos + _distribution(_generator) * dt);
	}
protected:
	std::default_random_engine _generator;
	std::normal_distribution<float> _distribution;

	float _yPos;
};

int main(void)
{
    MB::GLContext context(3, 3, 1024, 768, "Brownian Motion");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene(engine);

	MB::Cube* cube = new MB::Cube(1.0f);

	MB::SimpleShadingMaterial material;
	material.uniform("color")->value(MB::Vect3(MB::Color3::Blue));

	MB::Node* mbCube = new MB::Node(std::string("cube"));
	mbCube->setMesh(new MB::MeshRenderer(cube, &material));
	mbCube->addComponent(new MB::MoveComponent());
	mbCube->addComponent(new MB::RotateComponent(MB::Axis::z));
	mbCube->addComponent(new BrownianMovement());
	mbCube->transform().position().set(0.0f, 3.0f, 0.0f);

	scene->root()->addChild(mbCube);

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
	if (MB::Input2::isKeyPressed(MB::Keyboard::Key::Z))
	{
		engine->state()->depth.setStatus(false);
	}
	if (MB::Input2::isKeyPressed(MB::Keyboard::Key::X))
	{
		engine->state()->depth.setStatus(true);
	}
	if (MB::Input2::isKeyPressed(MB::Keyboard::Key::K))
	{
		engine->state()->culling.setStatus(false);
	}
	if (MB::Input2::isKeyPressed(MB::Keyboard::Key::L))
	{
		engine->state()->culling.setStatus(true);
	}
	if (MB::Input2::isKeyPressed(MB::Keyboard::Key::M))
	{
		engine->state()->setPolygonMode(GL_FILL);
	}
	if (MB::Input2::isKeyPressed(MB::Keyboard::Key::N))
	{
		engine->state()->setPolygonMode(GL_LINE);
	}
	if (MB::Input2::isKeyPressed(MB::Keyboard::Key::Num1))
	{
		engine->state()->culling.setFlipSided(GL_CCW);
	}
	if (MB::Input2::isKeyPressed(MB::Keyboard::Key::Num2))
	{
		engine->state()->culling.setFlipSided(GL_CW);
	}
	scene->render(dt);
}
