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

#include <thread>

mb::Engine* engine;
mb::Scene* scene;

void renderFunc(float dt);

mb::Node* mbModel;
mb::CustomPingPong<mb::Texture2D*>* customPP;

int main(void)
{
	mb::GLContext context(4, 3, 1024, 768, "Tex Swap");

    engine = new mb::Engine(&context, false);
    scene = new mb::Scene(engine);

    customPP = new mb::CustomPingPong<mb::Texture2D*>(
		new mb::Texture2D({}, MB_TEXTURE_ASSETS + std::string("/Dundus_Square.jpg")),
		new mb::Texture2D({}, MB_TEXTURE_ASSETS + std::string("/matcap.jpg"))
    );

	mb::Cube* model = new mb::Cube(1.0f);

	std::vector<std::pair<mb::ShaderType, const char*> > shaders;
	const char* vertexShader =
		"#version 330\n"
		"layout(location = 0) in vec3 position;"
		"layout(location = 1) in vec3 normal;"
		"layout(location = 2) in vec2 uv;"
		"out vec3 outNormal;"
		"out vec2 outUV;"
		"uniform mat4 projection;"
		"uniform mat4 view;"
		"uniform mat4 model;"
		"void main() {"
		"	vec3 outPosition = vec3(model * vec4(position, 1.0));"
		"	gl_Position = projection * view * vec4(outPosition, 1.0);"
		"	mat3 normalMatrix = mat3(inverse(transpose(model)));"
		"	outNormal = normalize(normalMatrix * normal);"
		"	outUV = uv;"
		"}";
	const char* fragmentShader =
		"#version 330\n"
		"in vec3 outNormal;"
		"in vec2 outUV;"
		"out vec4 fragColor;"
		"uniform vec3 viewPos;"
		"uniform sampler2D tex;"
		"void main() {"
		"	fragColor = vec4(texture(tex, outUV).rgb, 1.0);"
		"}";

	shaders.push_back(std::make_pair(mb::VertexShader, vertexShader));
	shaders.push_back(std::make_pair(mb::FragmentShader, fragmentShader));

	std::vector<std::pair<const char*, mb::Uniform*> > uniforms;
	uniforms.push_back(std::make_pair("projection", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("view", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("model", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("viewPos", new mb::Uniform(mb::Vector3)));
	uniforms.push_back(std::make_pair("tex", new mb::Uniform(mb::Integer, 0)));

	mb::ShaderMaterial material("textureShader", shaders, uniforms);

	mbModel = new mb::Node(std::string("cube"));
	mbModel->setMesh(new mb::MeshRenderer(model, &material));
	mbModel->addComponent(new mb::MoveComponent());
	mbModel->addComponent(new mb::RotateComponent(mb::Axis::x));

	mbModel->getComponent<mb::RotateComponent>()->setRotate(true);

	scene->root()->addChild(mbModel);

	customPP->first()->bind(0);

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}

float ms = 0.0f;
void renderFunc(float dt)
{
	ms += dt;
	if (ms >= 1.0f)
	{
		customPP->swap();
		customPP->first()->bind(0);
		ms = 0.0f;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->camera->update(dt);
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
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::P))
	{
		mbModel->toggleComponent<mb::MoveComponent>();
	}
	scene->render(dt);
}
