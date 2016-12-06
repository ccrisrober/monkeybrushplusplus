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

class AllRotationComponent : public mb::Component
{
public:
	AllRotationComponent() : mb::Component()
	{
	}
	virtual void update(float dt)
	{
		auto transform = this->_node->transform();
		float rotX = transform.rotation().x() + (speed * dt);
		float rotY = transform.rotation().y() + (speed * dt);
		float rotZ = transform.rotation().z() + (speed * dt);
		/*std::cout << rotX << ", " << rotY << ", " << rotZ << std::endl;
		transform.rotation().set(
			rotX, rotY, rotZ
		);*/
		this->_node->transform().rotation().set(rotX, rotY, rotZ);
	}
	float speed = 1.0f;
};

void renderFunc(float dt);

mb::Node* mbModel;

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Orbit Pivot");

    engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::SimpleShadingMaterial material;
	material.uniform("color")->value(mb::Vect3(mb::Color3::Blue));
	material.Cull = false;
	material.PolygonMode = GL_LINE;

	mb::SimpleShadingMaterial material2;
	material2.uniform("color")->value(mb::Vect3(mb::Color3::Red));
	material2.Cull = false;
	material2.PolygonMode = GL_LINE;

	mb::Drawable* model = new mb::Cube(13.0f);
	mb::Drawable* model2 = new mb::Cube(4.0f);

	mb::Node* innerNode = new mb::Node("innerNode");
	innerNode->transform().position().set(0.0f, 1.0f, 0.0f);
	innerNode->setMesh(new mb::MeshRenderer(model, &material));
	scene->root()->addChild(innerNode);
	mb::Node* pivot = new mb::Node("pivot");
	innerNode->addChild(pivot);
	mb::Node* outerNode = new mb::Node("outerNode");
	outerNode->transform().position().set(14.0f, 4.0f, 6.0f);

	outerNode->setMesh(new mb::MeshRenderer(model2, &material2));
	pivot->addChild(outerNode);
	pivot->addComponent(new AllRotationComponent());

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->mainCamera->update(dt);
	scene->render(dt);
}
