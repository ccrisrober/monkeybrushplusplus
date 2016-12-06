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

float tesslevel = 2.0f;

int main(void)
{
	mb::GLContext context(4, 4, 1024, 768, "Triangle tesselation");

    engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::Drawable* model = new mb::Icosahedron(1.0f);

	std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
		{
			mb::VertexShader,
			"#version 440																		\n"
			"layout(location = 0) in vec3 position;												\n"
			"uniform mat4 projection;															\n"
			"uniform mat4 view;																	\n"
			"uniform mat4 model;																\n"
			"void main() {																		\n"
			"	gl_Position = projection * view * model * vec4(position, 1.0f);					\n"
			"}                                                                                 	\n"
		},{
			mb::TesselationControlShader,
			"#version 440																		\n"
			"layout (vertices = 3) out;															\n"
			"uniform float tess_level;															\n"
			"void main(void) {                                                                  \n"
			"    if (gl_InvocationID == 0) {                                                  	\n"
			"        gl_TessLevelInner[0] = tess_level;                                        	\n"
			"        gl_TessLevelOuter[0] = tess_level;                                        	\n"
			"        gl_TessLevelOuter[1] = tess_level;                                        	\n"
			"        gl_TessLevelOuter[2] = tess_level;                                        	\n"
			"    }                                                                             	\n"
			"    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;     	\n"
			"}                                                                                 	\n"
		}, {
			mb::TesselationEvaluationShader,
			"#version 440																		\n"
			"layout (triangles) in;                                                            	\n"
			"void main(void) {                                                                	\n"
			"    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +                       	\n"
			"                  (gl_TessCoord.y * gl_in[1].gl_Position) +                       	\n"
			"                  (gl_TessCoord.z * gl_in[2].gl_Position);                        	\n"
			"}                                                                                 	\n"
		}, {
			mb::FragmentShader,
			"#version 440																		\n"
			"out vec4 fragColor;																\n"
			"uniform vec3 color;																\n"
			"void main() {																		\n"
			"	fragColor = vec4(color, 1.0);													\n"
			"}                                                                                 	\n"
		}
	};

	std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
		std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
		std::make_pair("view", new mb::Uniform(mb::Matrix4)),
		std::make_pair("model", new mb::Uniform(mb::Matrix4)),
		std::make_pair("color", new mb::Uniform(mb::Vector3, mb::Vect3(mb::Color3::Pink))),
		std::make_pair("tess_level", new mb::Uniform(mb::Float, tesslevel))
	};

	mb::ShaderMaterial material("triangleTesselation", shaders, uniforms);
	material.Cull = false;
	material.PolygonMode = GL_LINE;

	mbModel = new mb::Node(std::string("model"));
	mbModel->setMesh(new mb::MeshRendererTesselation(model, &material));	// Same as MeshRenderer(model, &material, GL_PATCHES)
	mbModel->addComponent(new mb::MoveComponent());

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
	if (mb::Input::isKeyPressed(mb::Keyboard::Key::Plus))
	{
		tesslevel += 0.1f;
		mbModel->getMesh()->getMaterial()->uniform("tess_level")->value(tesslevel);
	} else if (mb::Input::isKeyPressed(mb::Keyboard::Key::Minus))
	{
		tesslevel -= 0.1f;
		mbModel->getMesh()->getMaterial()->uniform("tess_level")->value(tesslevel);
	}
	scene->render(dt);
}
