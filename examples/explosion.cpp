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
#include <vector>

mb::Engine* engine;
mb::Scene* scene;

void renderFunc(float dt);

mb::Node* mbObj;
mb::Node* mbObj2;
mb::Node* mbObj3;
mb::ShaderMaterial* material;

int main(void)
{
    mb::GLContext context(3, 3, 1024, 768, "Hello mb");

    engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);


	std::vector<std::pair<mb::ShaderType, const char*> > shaders;
	const char* vertexShader =
		"#version 330 core\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 2) in vec2 texCoords;\n"
		"out VS_OUT {\n"
		"	vec2 texCoords;\n"
		"} vs_out;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"void main() {\n"
		"	gl_Position = projection * view * model * vec4(position, 1.0f);\n"
		"	vs_out.texCoords = texCoords;\n"
		"}";
	const char* geometryShader =
		"#version 330 core\n"
		"layout (triangles) in;\n"
		"layout (triangle_strip, max_vertices = 3) out;\n"
		"in VS_OUT {\n"
		"    vec2 texCoords;\n"
		"} gs_in[];\n"
		"out vec2 TexCoords; \n"
		"uniform float time;\n"
		"vec4 explode(vec4 position, vec3 normal) {\n"
		"    float magnitude = 2.0f;\n"
		"    vec3 direction = normal * ((sin(time) + 1.0f) / 2.0f) * magnitude; \n"
		"    return position + vec4(direction, 0.0f);\n"
		"}\n"
		"vec3 GetNormal() {\n"
		"    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);\n"
		"    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);\n"
		"    return normalize(cross(a, b));\n"
		"}\n"
		"void main() {\n"
		"    vec3 normal = GetNormal();\n"
		"    gl_Position = explode(gl_in[0].gl_Position, normal);\n"
		"    TexCoords = gs_in[0].texCoords;\n"
		"    EmitVertex();\n"
		"    gl_Position = explode(gl_in[1].gl_Position, normal);\n"
		"    TexCoords = gs_in[1].texCoords;\n"
		"    EmitVertex();\n"
		"    gl_Position = explode(gl_in[2].gl_Position, normal);\n"
		"    TexCoords = gs_in[2].texCoords;\n"
		"    EmitVertex();\n"
		"    EndPrimitive();\n"
		"}";
	const char* fragmentShader =
		"#version 330\n"
		"out vec4 fragColor;\n"
		"uniform vec3 color;\n"
		"void main() {\n"
		"	fragColor = vec4(color, 1.0);\n"
		"}";

	shaders.push_back(std::make_pair(mb::VertexShader, vertexShader));
	shaders.push_back(std::make_pair(mb::GeometryShader, geometryShader));
	shaders.push_back(std::make_pair(mb::FragmentShader, fragmentShader));


	std::vector<std::pair<const char*, mb::Uniform*> > uniforms;
	uniforms.push_back(std::make_pair("projection", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("view", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("model", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("color", new mb::Uniform(mb::Vector3, mb::Vect3(0.0f, 1.0f, 1.0f))));
	uniforms.push_back(std::make_pair("time", new mb::Uniform(mb::Float, 0.015f)));

	material = new mb::ShaderMaterial("geomExplosion", shaders, uniforms);

	mb::Torus* torus = new mb::Torus(0.5f, 0.25f, 25, 40);

	mbObj = new mb::Node(std::string("torus"));
	mbObj->setMesh(new mb::MeshRenderer(torus, material));
	mbObj->addComponent(new mb::MoveComponent());
	mbObj->addComponent(new mb::RotateComponent(mb::Axis::x));
	mbObj->transform().position().y(3.5f);
	mbObj->transform().rotation().y(-1.44f);

	mbObj2 = new mb::Node(std::string("torus"));
	mbObj2->setMesh(new mb::MeshRenderer(torus, material));
	mbObj2->addComponent(new mb::MoveComponent());
	mbObj2->addComponent(new mb::RotateComponent(mb::Axis::y));
	mbObj2->transform().position().y(0.0f);

	mbObj3 = new mb::Node(std::string("torus"));
	mbObj3->setMesh(new mb::MeshRenderer(torus, material));
	mbObj3->addComponent(new mb::MoveComponent());
	mbObj3->addComponent(new mb::RotateComponent(mb::Axis::z));
	mbObj3->transform().position().y(-3.5f);
	mbObj3->transform().rotation().x(1.44f/2.0f);


	scene->root()->addChild(mbObj);
	scene->root()->addChild(mbObj2);
	scene->root()->addChild(mbObj3);

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}
float globalTime = 0.0f;
void renderFunc(float dt)
{
	globalTime += dt;
	glDisable(GL_CULL_FACE);
	material->uniform("time")->value(globalTime);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->mainCamera->update(dt);
	if (mb::Input::isKeyPressed(mb::Keyboard::Key::Esc))
	{
		engine->close();
		return;
	}
	scene->render(dt);
}
