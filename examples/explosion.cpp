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

MB::Engine* engine;
MB::Scene* scene;

void renderFunc(float dt);

MB::Node* mbObj;
MB::Node* mbObj2;
MB::Node* mbObj3;
MB::ShaderMaterial* material;

int main(void)
{
    MB::GLContext context(3, 3, 1024, 768, "Hello MB");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene();


	std::vector<std::pair<MB::ShaderType, const char*> > shaders;
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

	shaders.push_back(std::make_pair(MB::VertexShader, vertexShader));
	shaders.push_back(std::make_pair(MB::GeometryShader, geometryShader));
	shaders.push_back(std::make_pair(MB::FragmentShader, fragmentShader));


	std::vector<std::pair<const char*, MB::Uniform*> > uniforms;
	uniforms.push_back(std::make_pair("projection", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("view", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("model", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("color", new MB::Uniform(MB::Vector3, MB::Vect3(0.0f, 1.0f, 1.0f))));
	uniforms.push_back(std::make_pair("time", new MB::Uniform(MB::Float, 0.015f)));

	material = new MB::ShaderMaterial("geomExplosion", shaders, uniforms);

	MB::Torus* torus = new MB::Torus(0.5f, 0.25f, 25, 40);

	mbObj = new MB::Node(std::string("torus"));
	mbObj->addComponent(new MB::MeshRenderer(torus, material));
	mbObj->addComponent(new MB::MoveComponent());
	mbObj->addComponent(new MB::RotateComponent(MB::Axis::x));
	mbObj->transform().position().y(3.5f);
	mbObj->transform().rotation().y(-1.44f);

	mbObj2 = new MB::Node(std::string("torus"));
	mbObj2->addComponent(new MB::MeshRenderer(torus, material));
	mbObj2->addComponent(new MB::MoveComponent());
	mbObj2->addComponent(new MB::RotateComponent(MB::Axis::y));
	mbObj2->transform().position().y(0.0f);

	mbObj3 = new MB::Node(std::string("torus"));
	mbObj3->addComponent(new MB::MeshRenderer(torus, material));
	mbObj3->addComponent(new MB::MoveComponent());
	mbObj3->addComponent(new MB::RotateComponent(MB::Axis::z));
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
	scene->camera->update(dt);
	if (MB::Input2::isKeyPressed(MB::Keyboard::Key::Esc))
	{
		engine->close();
		return;
	}
	scene->render(dt);
}
