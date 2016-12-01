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

float amount = 0.05f;

mb::ShaderMaterial* material;

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Hello mb");

    engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::Polyhedron* model = new mb::Tetrahedron(1.0f, 2);

	std::vector<std::pair<mb::ShaderType, const char*> > shaders;
	const char* vertexShader =
		"#version 330\n"
		"layout(location = 0) in vec3 position;"
		"layout(location = 1) in vec3 normal;"
		"out vec3 outPosition;"
		"out vec3 outNormal;"
		"uniform mat4 projection;"
		"uniform mat4 view;"
		"uniform mat4 model;"
		"uniform float amount;"
		"void main() {"
		"	mat3 normalMatrix = mat3(inverse(transpose(model)));"
		"	outNormal = normalize(normalMatrix * normal);"
		"	outPosition = position + (normal * amount);"
		"	outPosition = vec3(view * model * vec4(outPosition, 1.0));"
		"	gl_Position = projection * vec4(outPosition, 1.0);"
		"}";
	const char* fragmentShader =
		"#version 330\n"
		"in vec3 outPosition;"
		"in vec3 outNormal;"
		"out vec4 fragColor;"
		"uniform vec3 viewPos;"
		"void main() {"
		"	vec3 color = vec3(1.0, 0.0, 0.0);"
		"	vec3 N = normalize(outNormal);"
		"	vec3 L = normalize(viewPos - outPosition);"
		"	float dif = dot(N, L);"
		"	dif = clamp(dif, 0.0, 1.0);"
		"	fragColor = vec4(color * dif, 1.0) + vec4(color * 0.3, 1.0);"
		"}";

	shaders.push_back(std::make_pair(mb::VertexShader, vertexShader));
	shaders.push_back(std::make_pair(mb::FragmentShader, fragmentShader));

	std::vector<std::pair<const char*, mb::Uniform*> > uniforms;
	uniforms.push_back(std::make_pair("projection", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("view", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("model", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("viewPos", new mb::Uniform(mb::Vector3)));
	uniforms.push_back(std::make_pair("amount", new mb::Uniform(mb::Float, amount)));

	material = new mb::ShaderMaterial("textureShader", shaders, uniforms);

	mbModel = new mb::Node(std::string("model"));
	mbModel->transform().scale().set(0.25f, 0.25f, 0.25f);
	mbModel->setMesh(new mb::MeshRenderer(model, material));
	mbModel->addComponent(new mb::RotateComponent(mb::Axis::x));

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
	if (mb::Input::isKeyPressed(mb::Keyboard::Key::M))
	{
		amount += 0.01f;
		material->uniform("amount")->value(amount);
	} else if (mb::Input::isKeyPressed(mb::Keyboard::Key::N))
	{
		amount -= 0.01f;
		material->uniform("amount")->value(amount);
	}
	engine->state()->culling.setStatus(false);
	//engine->state()->setPolygonMode(GL_LINE);
	scene->render(dt);
}
