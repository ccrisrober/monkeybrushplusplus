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

MB::Engine* engine;
MB::Scene* scene;

void renderFunc(float dt);

MB::Node* mbCube;
MB::RotateComponent* r;

class SplineMovement : public MB::Component
{
public:
	SplineMovement()
		: Component()
		, t(0.0f)
	{
	}
	void start()
	{
		el = new MB::curves::Ellipse(
			MB::Vect2(0.5f, 0.0f),
			MB::Vect2(3.2f, 2.5f),
			0.0f, 2.0f * MB::Mathf::PI, false);
	}
	void update(float dt)
	{
		t += (dt / 10.0f);
		if (t > 1.0f) t = 0.0f;

		MB::Vect2 v = el->evaluate(t);
		_node->transform().position().set(v.x(), v.y(), -5.0f);
	}
protected:
	float t;
	MB::curves::Ellipse *el;
};

int main(void)
{
    MB::GLContext context(3, 3, 1024, 768, "Hello MB");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene();

	MB::Torus* torus = new MB::Torus(0.5f, 0.25f, 25, 40);

	std::vector<std::pair<MB::ShaderType, const char*> > shaders;
	const char* vertexShader =
		"#version 330\n"
		"layout(location = 0) in vec3 position;"
		"layout(location = 1) in vec3 normal;"
		"out vec3 outNormal;"
		"uniform mat4 projection;"
		"uniform mat4 view;"
		"uniform mat4 model;"
		"void main() {"
		"	vec3 outPosition = vec3(model * vec4(position, 1.0));"
		"	gl_Position = projection * view * vec4(outPosition, 1.0);"
		"	mat3 normalMatrix = mat3(inverse(transpose(model)));"
		"	outNormal = normalize(normalMatrix * normal);"
		"}";
	const char* fragmentShader =
		"#version 330\n"
		"in vec3 outNormal;"
		"out vec4 fragColor;"
		"uniform vec3 viewPos;"
		"uniform sampler2D tex;"
		"vec2 matcap(vec3 eye, vec3 normal) {\n"
		"	vec3 reflected = reflect(eye, normal);\n"
		"	float m = 2.0 * sqrt(\n"
		"		pow(reflected.x, 2.0) +\n"
		"		pow(reflected.y, 2.0) +\n"
		"		pow(reflected.z + 1.0, 2.0)\n"
		"	);\n"
		"	return reflected.xy / m + 0.5;\n"
		"}\n"
		"void main() {"
		"	vec2 uv = matcap(viewPos, outNormal);"
		"	fragColor = vec4(texture(tex, uv).rgb, 1.0);"
		"}";

	shaders.push_back(std::make_pair(MB::VertexShader, vertexShader));
	shaders.push_back(std::make_pair(MB::FragmentShader, fragmentShader));

	std::vector<std::pair<const char*, MB::Uniform*> > uniforms;
	uniforms.push_back(std::make_pair("projection", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("view", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("model", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("viewPos", new MB::Uniform(MB::Vector3)));
	uniforms.push_back(std::make_pair("tex", new MB::Uniform(MB::Integer, 0)));

	MB::ShaderMaterial material("textureShader", shaders, uniforms);

	mbCube = new MB::Node(std::string("cube"));
	mbCube->addComponent(new MB::MeshRenderer(torus, &material));
	mbCube->addComponent(new SplineMovement());
	r = new MB::RotateComponent(MB::Axis::x);
	mbCube->addComponent(r);

	MB::TexOptions opts;
	MB::Texture2D* tex = new MB::Texture2D(opts, MB_TEXTURE_ASSETS + std::string("/matcap.jpg"));
	tex->bind(0);

	scene->root()->addChild(mbCube);

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->camera->update(dt);
	if (MB::Input::isKeyPressed(GLFW_KEY_ESCAPE))
	{
		engine->close();
		return;
	}
	if (MB::Input::isKeyClicked(GLFW_KEY_X))
	{
		r->setAxis(MB::Axis::x);
		//mbCube->getComponent<MB::RotateComponent>()->setAxis(MB::Axis::x);
	}
	else if (MB::Input::isKeyClicked(GLFW_KEY_Y))
	{
		r->setAxis(MB::Axis::y);
		//mbCube->getComponent<MB::RotateComponent>()->setAxis(MB::Axis::y);
	}
	else if (MB::Input::isKeyClicked(GLFW_KEY_Z))
	{
		r->setAxis(MB::Axis::z);
		//mbCube->getComponent<MB::RotateComponent>()->setAxis(MB::Axis::z);
	}
	scene->render(dt);
}
