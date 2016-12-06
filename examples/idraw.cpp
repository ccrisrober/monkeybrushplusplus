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
	mb::GLContext context(3, 3, 1024, 768, "Hello mb");

	engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
		{
			mb::VertexShader,
			"#version 330\n"
			"layout(location = 0) in vec3 position;"
			"layout(location = 1) in vec3 offset;"
			"layout(location = 2) in vec3 color;"
			"uniform mat4 projection;"
			"uniform mat4 view;"
			"uniform mat4 model;"
			"out vec3 outColor;"
			"void main() {"
			"	vec3 outPosition = vec3(model * vec4(position, 1.0));"
			"	gl_Position = projection * view * vec4(outPosition + offset, 1.0);"
			"	outColor = color;"
			"}"
		},{
			mb::FragmentShader,
			"#version 330\n"
			"in vec3 outColor;"
			"out vec4 fragColor;"
			"vec3 color = vec3(1.0);"
			"void main() {"
			"	fragColor = vec4(outColor, 1.0);"
			"}"
		}
	};

	std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
		std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
		std::make_pair("view", new mb::Uniform(mb::Matrix4)),
		std::make_pair("model", new mb::Uniform(mb::Matrix4)),
	};

	mb::ShaderMaterial material("material", shaders, uniforms);
	//material.PolygonMode = GL_LINE;
	material.Cull = false;

	mbModel = new mb::Node(std::string("model"));
	mbModel->setMesh(new mb::MeshRenderer(new mb::ArraysDrawable(), &material));
	mbModel->addComponent(new mb::MoveComponent());
	
	scene->root()->addChild(mbModel);

	engine->run(renderFunc);

	delete(scene);
	delete(engine);

	return 0;
}

void renderFunc(float dt)
{
	glClearColor(1.0f, 1.0f, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->mainCamera->update(dt);
	scene->render(dt);
}
