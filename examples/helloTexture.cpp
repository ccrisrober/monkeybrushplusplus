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

mb::Node* mbCube;
mb::RotateComponent* r;

class SplineMovement : public mb::Component
{
public:
	SplineMovement()
		: Component()
		, t(0.0f)
	{
	}
	void start()
	{
		el = new mb::curves::Ellipse(
			mb::Vect2(0.5f, 0.0f),
			mb::Vect2(3.2f, 2.5f),
			0.0f, 2.0f * mb::Mathf::PI, false);
	}
	void update(float dt)
	{
		t += (dt / 10.0f);
		if (t > 1.0f) t = 0.0f;

		mb::Vect2 v = el->evaluate(t);
		_node->transform().position().set(v.x(), v.y(), -5.0f);
	}
protected:
	float t;
	mb::curves::Ellipse *el;
};

int main(void)
{
    mb::GLContext context(3, 3, 1024, 768, "Hello mb");

    engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::Torus* torus = new mb::Torus(0.5f, 0.25f, 25, 40);

	std::vector<std::pair<mb::ShaderType, const char*> > shaders;
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

	shaders.push_back(std::make_pair(mb::VertexShader, vertexShader));
	shaders.push_back(std::make_pair(mb::FragmentShader, fragmentShader));

	mb::TexOptions opts;
	mb::Texture* tex = new mb::Texture2D(opts, MB_TEXTURE_ASSETS + std::string("/matcap.jpg"));

	std::vector<std::pair<const char*, mb::Uniform*> > uniforms;
	uniforms.push_back(std::make_pair("projection", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("view", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("model", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("viewPos", new mb::Uniform(mb::Vector3)));
	uniforms.push_back(std::make_pair("tex", new mb::Uniform(mb::TextureSampler, tex)));

	mb::ShaderMaterial material("textureShader", shaders, uniforms);

	mbCube = new mb::Node(std::string("cube"));
	mbCube->setMesh(new mb::MeshRenderer(torus, &material));
	mbCube->addComponent(new SplineMovement());
	r = new mb::RotateComponent(mb::Axis::x);
	mbCube->addComponent(r);

	scene->root()->addChild(mbCube);

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
		r->setAxis(mb::Axis::x);
		//mbCube->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::x);
	}
	else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Y))
	{
		r->setAxis(mb::Axis::y);
		//mbCube->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::y);
	}
	else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Z))
	{
		r->setAxis(mb::Axis::z);
		//mbCube->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::z);
	}
	scene->render(dt);
}
