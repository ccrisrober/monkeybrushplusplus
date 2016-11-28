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
#include <rapidjson/document.h>

mb::Engine* engine;
mb::Scene* scene;

void renderFunc(float dt);

using namespace rapidjson;

mb::Cube* model;

mb::SimpleShadingMaterial *material;

void addObjectToScene(const rapidjson::Value& children, mb::Node* node)
{
	for (SizeType i = 0, len = children.Size(); i < len; ++i)
	{
		const Value& child = children[i];
		mb::Node* mbModel = new mb::Node(std::string(child["name"].GetString()));
		mbModel->setMesh(new mb::MeshRenderer(model, material));

		const Value& transform = child["transform"];
		const Value& position = transform["position"];

		mbModel->transform().position().set(
			(float)position[0].GetDouble(), 
			(float)position[1].GetDouble(), 
			(float)position[2].GetDouble()
		);

		if (transform.HasMember("scale"))
		{
			const Value& scale = transform["scale"];

			mbModel->transform().scale().set(
				(float)scale[0].GetDouble(), 
				(float)scale[1].GetDouble(), 
				(float)scale[2].GetDouble()
			);
		}

		if (child.HasMember("components"))
		{
			const Value& comp = child["components"][0];
			std::string name = comp["name"].GetString();
			if (name == "RotateComponent")
			{
				mb::RotateComponent * rc = new mb::RotateComponent(comp["data"]);
				if (rc) 
				{
					mbModel->addComponent(rc);
				}
			} else if (name == "MoveComponent")
			{
				mbModel->addComponent(new mb::MoveComponent());
			}
		}

		node->addChild(mbModel);

		if (child.HasMember("children"))
		{
			addObjectToScene(child["children"], mbModel);
		}
	}
}

int main(void)
{
	std::ifstream file(MB_FILES_ASSETS + std::string("/scene.json"));
	std::stringstream buffer;
	buffer << file.rdbuf();

	rapidjson::Document document;
	document.Parse(buffer.str().c_str());

	std::cout << document.HasMember("objects") << std::endl;
	std::cout << document["objects"].IsArray() << std::endl;

	mb::GLContext context(4, 3, 512, 512, "Hello mb");

    engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	model = new mb::Cube(1.0f);

	material = new mb::SimpleShadingMaterial();
	material->uniform("color")->value(mb::Vect3(mb::Color3::Blue));

	addObjectToScene(document["objects"], scene->root());

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->camera->update(dt);
	if (mb::Input::isKeyPressed(mb::Keyboard::Key::Esc))
	{
		engine->close();
		return;
	}
	// engine->state()->culling.setStatus(false);
	// engine->state()->setPolygonMode(GL_LINE);
	scene->render(dt);
}
