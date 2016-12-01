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

class Rotate : public mb::Component
{
public:
	Rotate()
		: mb::Component()
		, _rotate(false)
	{
	}
	virtual void update(float dt)
	{
		if (mb::Input::isKeyClicked(mb::Keyboard::Key::Space))
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
	mb::GLContext context(3, 3, 1024, 768, "Hello mb");

	engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::Cube* cube = new mb::Cube(2.0f);

	unsigned int MAX = 25;
	for (unsigned int yy = 0; yy < MAX; ++yy)
	{
		for (unsigned int xx = 0; xx < MAX; ++xx)
		{
			mb::Node* mbCube = new mb::Node(std::string("cube"));

			mb::SimpleShadingMaterial* material = new mb::SimpleShadingMaterial();
			material->uniform("color")->value(mb::Vect3(mb::Color3((float)xx / MAX, (float)yy / MAX, 0.1f)));

			mbCube->setMesh(new mb::MeshRenderer(cube, material));
			mbCube->addComponent(new Rotate());
			mbCube->transform().position().set(
				-15.0f + xx * 3.0f,
				-15.0f + yy * 3.0f,
				0.0f);
			mbCube->transform().rotation().z(xx * 0.21f + yy + 0.37f);
			scene->root()->addChild(mbCube);
			//.rotate(this.angle + xx * 0.21 + yy * 0.37, mb.Vect3.zAxis);
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
	scene->mainCamera->update(dt);
	if (mb::Input::isKeyPressed(mb::Keyboard::Key::Esc))
	{
		engine->close();
		return;
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::Z))
	{
		engine->state()->depth.setStatus(false);
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::X))
	{
		engine->state()->depth.setStatus(true);
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::K))
	{
		engine->state()->culling.setStatus(false);
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::L))
	{
		engine->state()->culling.setStatus(true);
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::M))
	{
		engine->state()->setPolygonMode(GL_FILL);
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::N))
	{
		engine->state()->setPolygonMode(GL_LINE);
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::Num1))
	{
		engine->state()->culling.setFlipSided(GL_CCW);
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::Num2))
	{
		engine->state()->culling.setFlipSided(GL_CW);
	}
	scene->render(dt);
}