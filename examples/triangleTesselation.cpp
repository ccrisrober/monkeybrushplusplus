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

mb::Node* mbMesh;

int main(void)
{
    mb::GLContext context(4, 4, 1024, 768, "Triangle Tesselation");

    engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::Mesh* mesh = new mb::Mesh(MB_MODEL_ASSETS + std::string("/suzanne.obj_"));

	const char *vertexShader, *tessEvalShader, *tessControlShader, *fragmentShader;

	std::vector<std::pair<mb::ShaderType, const char*> > shaders;
	//{
		std::ifstream file1(MB_FILES_ASSETS + std::string("/tess/vertex.glsl"));
		std::stringstream buffer1;
		buffer1 << file1.rdbuf();
		std::string src1 = buffer1.str();
		vertexShader = src1.c_str();
	//}
	//{
		std::ifstream file2(MB_FILES_ASSETS + std::string("/tess/eval.glsl"));
		std::stringstream buffer2;
		buffer2 << file2.rdbuf();
		std::string src2 = buffer2.str();
		tessEvalShader = src2.c_str();
	//}
	//{
		std::ifstream file3(MB_FILES_ASSETS + std::string("/tess/control.glsl"));
		std::stringstream buffer3;
		buffer3 << file3.rdbuf();
		std::string src3 = buffer3.str();
		tessControlShader = src3.c_str();
	//}
	//{
		std::ifstream file4(MB_FILES_ASSETS + std::string("/tess/fragment.glsl"));
		std::stringstream buffer4;
		buffer4 << file4.rdbuf();
		std::string src4 = buffer4.str();
		fragmentShader = src4.c_str();
	//}

	shaders.push_back(std::make_pair(mb::VertexShader, vertexShader));
	shaders.push_back(std::make_pair(mb::TesselationControlShader, tessControlShader));
	shaders.push_back(std::make_pair(mb::TesselationEvaluationShader, tessEvalShader));
	shaders.push_back(std::make_pair(mb::FragmentShader, fragmentShader));


	std::vector<std::pair<const char*, mb::Uniform*> > uniforms;
	uniforms.push_back(std::make_pair("projection", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("view", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("model", new mb::Uniform(mb::Matrix4)));

	mb::ShaderMaterial material("triangleTesselation", shaders, uniforms);


	mbMesh = new mb::Node(std::string("mesh"));
	mbMesh->setMesh(new mb::MeshRenderer(mesh, &material, GL_PATCHES));
	mbMesh->addComponent(new mb::MoveComponent());
	mbMesh->addComponent(new mb::RotateComponent(mb::Axis::x));

	GLint MaxPatchVertices = 0;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
	printf("Max supported patch vertices %d\n", MaxPatchVertices);

	scene->root()->addChild(mbMesh);

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->camera->update(dt);
	engine->state()->setPolygonMode(GL_LINE);
	if (mb::Input::isKeyPressed(mb::Keyboard::Key::Esc))
	{
		engine->close();
		return;
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::C))
	{
		engine->state()->culling.setStatus(true);
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::V))
	{
		engine->state()->culling.setStatus(false);
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
	scene->render(dt);
}
