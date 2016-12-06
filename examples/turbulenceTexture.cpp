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
#include <shaderFiles.h>

mb::Engine* engine;
mb::Scene* scene;

void renderFunc(float dt);

mb::Node* mbMesh;
float base_freq = 6.9f;

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Turbulence Texture");

	engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::Mesh* mesh = new mb::Mesh(MB_MODEL_ASSETS + std::string("/suzanne.obj_"));

	mb::ResourceShader::loadShader(std::string("SimpleNoise3D"), MB_SHADERBACKUP_FILES + std::string("/SimpleNoise3D.glsl"));

	std::ifstream file1(MB_SHADER_FILES + std::string("/alienVertex.glsl"));
	std::stringstream buffer1;
	buffer1 << file1.rdbuf();
	std::string vertexShader = buffer1.str();

	std::ifstream file2(MB_SHADER_FILES + std::string("/turbulenceFrag.glsl"));
	std::stringstream buffer2;
	buffer2 << file2.rdbuf();
	std::string fragmentShader = buffer2.str();

	std::vector<std::pair<mb::ShaderType, const char*> > shaders;
	shaders.push_back(std::make_pair(mb::VertexShader, vertexShader.c_str()));
	shaders.push_back(std::make_pair(mb::FragmentShader, fragmentShader.c_str()));

	std::vector<std::pair<const char*, mb::Uniform*> > uniforms;
	uniforms.push_back(std::make_pair("projection", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("view", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("model", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("viewPos", new mb::Uniform(mb::Vector3)));
	uniforms.push_back(std::make_pair("base_freq", new mb::Uniform(mb::Float, base_freq)));

	mb::ShaderMaterial material("turbulenceMaterial", shaders, uniforms);

	mbMesh = new mb::Node(std::string("mesh"));
	mbMesh->setMesh(new mb::MeshRenderer(mesh, &material));
	mbMesh->addComponent(new mb::MoveComponent());
	mbMesh->addComponent(new mb::RotateComponent(mb::Axis::x));

	scene->root()->addChild(mbMesh);

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
		mbMesh->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::x);
	}
	else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Y))
	{
		mbMesh->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::y);
	}
	else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Z))
	{
		mbMesh->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::z);
	}
	if (mb::Input::isKeyPressed(mb::Keyboard::Key::O))
	{
		base_freq -= 0.01f;
		mbMesh->getMesh()->getMaterial()->uniform("base_freq")->value(base_freq);
	}
	if (mb::Input::isKeyPressed(mb::Keyboard::Key::P))
	{
		base_freq += 0.01f;
		mbMesh->getMesh()->getMaterial()->uniform("base_freq")->value(base_freq);
	}
	scene->render(dt);
}
