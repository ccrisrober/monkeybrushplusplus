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

class Rotate : public MB::Component
{
public:
	Rotate()
		: MB::Component()
		, _rotate(false)
	{
	}
	virtual void update(float dt)
	{
		if (MB::Input2::isKeyClicked(MB::Keyboard::Key::Space))
		{
			this->_rotate = !this->_rotate;
		}
		if (this->_rotate)
		{
			auto zRot = _node->transform().rotation().z();
			_node->transform().rotation().z(zRot + dt);
		}
	}
protected:
	bool _rotate;
};

int main(void)
{
	MB::GLContext context(3, 3, 1024, 768, "Hello MB");

	engine = new MB::Engine(&context, false);
	scene = new MB::Scene();

	MB::Cube* cube = new MB::Cube(2.0f);

	unsigned int MAX = 25;
	for (unsigned int yy = 0; yy < MAX; ++yy)
	{
		for (unsigned int xx = 0; xx < MAX; ++xx)
		{
			MB::Node* mbCube = new MB::Node(std::string("cube"));

			MB::SimpleShadingMaterial* material = new MB::SimpleShadingMaterial();
			material->uniform("color")->value(MB::Vect3(MB::Color3((float)xx / MAX, (float)yy / MAX, 0.1f)));

			mbCube->addComponent(new MB::MeshRenderer(cube, material));
			mbCube->addComponent(new Rotate());
			mbCube->transform().position().set(
				-15.0f + xx * 3.0f,
				-15.0f + yy * 3.0f,
				0.0f);
			mbCube->transform().rotation().z(xx * 0.21f + yy + 0.37f);
			scene->root()->addChild(mbCube);
			//.rotate(this.angle + xx * 0.21 + yy * 0.37, MB.Vect3.zAxis);
		}
	}

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
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::Z))
	{
		engine->state()->depth.setStatus(false);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::X))
	{
		engine->state()->depth.setStatus(true);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::K))
	{
		engine->state()->culling.setStatus(false);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::L))
	{
		engine->state()->culling.setStatus(true);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::M))
	{
		engine->state()->setPolygonMode(GL_FILL);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::N))
	{
		engine->state()->setPolygonMode(GL_LINE);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::Num1))
	{
		engine->state()->culling.setFlipSided(GL_CCW);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::Num2))
	{
		engine->state()->culling.setFlipSided(GL_CW);
	}
	scene->render(dt);
}