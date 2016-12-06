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

mb::Engine* engine;
mb::Scene* scene;

void renderFunc(float dt);

mb::Node* mbModel;

mb::ShaderMaterial* material;

float levels = 5.0f;

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Toon shading");

	engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::Mesh* model = new mb::Mesh(MB_MODEL_ASSETS + std::string("/suzanne.obj_"));

	std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
		{
			mb::VertexShader,
			"#version 330\n"
			"layout(location = 0) in vec3 position;\n"
			"layout(location = 1) in vec3 normal;\n"

			"out vec3 outPosition;\n"
			"out vec3 outNormal;\n"

			"uniform mat4 projection;\n"
			"uniform mat4 view;\n"
			"uniform mat4 model;\n"

			"void main() {\n"
			"	outPosition = vec3(model * vec4(position, 1.0));\n"
			"	gl_Position = projection * view * vec4(outPosition, 1.0);\n"
			"	mat3 normalMatrix = mat3(inverse(transpose(model)));\n"
			"	outNormal = normalize(normalMatrix * normal);\n"
			"}\n"
		},{
			mb::FragmentShader,
			"#version 330\n"
			"in vec3 outPosition;\n"
			"in vec3 outNormal; \n"

			"out vec4 fragColor; \n"

			"uniform sampler2D tex; \n"

			"uniform vec3 viewPos; \n"
			"uniform vec3 color; \n"

			"uniform float levels; // = 5.0;\n"

			"void main() {\n"
			"	float scaleFactor = 1.0 / levels; \n"
			"	vec3 n = normalize(outNormal); \n"
			"	vec3 s = normalize(viewPos.xyz - outPosition.xyz); \n"
			"	vec3 ambient = color * vec3(0.135, 0.2225, 0.1575); \n"
			"	float cosine = dot(s, n); \n"
			"	vec3 diffuse = color * floor(cosine * levels) * scaleFactor; \n"

			"	fragColor = vec4(vec3(ambient + diffuse), 1.0); \n"
			"}\n"
		}
	};

	std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
		std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
		std::make_pair("view", new mb::Uniform(mb::Matrix4)),
		std::make_pair("model", new mb::Uniform(mb::Matrix4)),
		std::make_pair("viewPos", new mb::Uniform(mb::Vector3)),
		std::make_pair("levels", new mb::Uniform(mb::Float, levels)),
		std::make_pair("color", new mb::Uniform(mb::Vector3, mb::Vect3(0.54f, 0.89f, 0.63f)))
	};

	material = new mb::ShaderMaterial("material", shaders, uniforms);

	mbModel = new mb::Node(std::string("model"));
	mbModel->setMesh(new mb::MeshRenderer(model, material));
	mbModel->addComponent(new mb::RotateComponent(mb::Axis::y, 0.15f));

	mbModel->getComponent<mb::RotateComponent>()->setRotate(true);

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
	if (mb::Input::isKeyPressed(mb::Keyboard::Key::Esc))
	{
		engine->close();
		return;
	}
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
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::Plus))
	{
		levels += 1.0f;
		material->uniform("levels")->value(levels);
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::Minus))
	{
		levels -= 1.0f;
		if (levels < 1.0f) levels = 1.0f;
		material->uniform("levels")->value(levels);
	}
	scene->render(dt);
}
