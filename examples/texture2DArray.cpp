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

float layer = 0.0f;

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Hello mb");

	engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::Drawable* torus = new mb::Torus(0.5f, 0.25f, 25, 40);

	std::vector<std::pair<mb::ShaderType, const char*> > shaders;
	const char* vertexShader =
		"#version 330\n"
		"layout(location = 0) in vec3 position;"
		"layout(location = 1) in vec2 uv;"
		"out vec2 outUV;"
		"uniform mat4 projection;"
		"uniform mat4 view;"
		"uniform mat4 model;"
		"void main() {"
		"	vec3 outPosition = vec3(model * vec4(position, 1.0));"
		"	gl_Position = projection * view * vec4(outPosition, 1.0);"
		"	outUV = uv;"
		"}";
	const char* fragmentShader =
		"#version 330\n"
		"in vec2 outUV;"
		"out vec4 fragColor;"
		"uniform sampler2DArray tex;"
		"uniform float layer;"
		"void main() {"
		"	fragColor = vec4(texture(tex, vec3(outUV, layer)).rgb, 1.0);"
		"}";

	shaders.push_back(std::make_pair(mb::VertexShader, vertexShader));
	shaders.push_back(std::make_pair(mb::FragmentShader, fragmentShader));

	mb::TexOptions opts;
	std::vector<void*> data;
	unsigned int texSize = 1024;
	std::vector<unsigned int> bb1(texSize * texSize * 3);
	unsigned int checkSize = 5;
	unsigned int n = 0;
	// Generate some checker board pattern
	for (unsigned int y = 0; y < texSize; ++y)
	{
		for (unsigned int x = 0; x < texSize; ++x)
		{
			if (((x / checkSize + y / checkSize) % 2) == 0)
			{
				bb1[n++] = 255;
				bb1[n++] = 255;
				bb1[n++] = 255;
			}
			else
			{
				bb1[n++] = 0;
				bb1[n++] = 0;
				bb1[n++] = 0;
			}
		}
	}
	data.push_back(bb1.data());

	std::vector<unsigned int> bb2(texSize * texSize * 3);
	n = 0;
	// Generate some diagonal lines for the second layer
	for (unsigned int y = 0; y < texSize; y++)
	{
		for (unsigned int x = 0; x < texSize; x++)
		{
			if ((x + y) / 3 % 3 == 0)
			{
				bb2[n++] = 255;
				bb2[n++] = 255;
				bb2[n++] = 255;
			}
			else
			{
				bb2[n++] = 128;
				bb2[n++] = 128;
				bb2[n++] = 128;
			}
		}
	}
	data.push_back(bb2.data());

	std::vector<unsigned int> bb3(texSize * texSize * 3);
	n = 0;
	// Generate some diagonal lines for the second layer
	for (unsigned int y = 0; y < texSize; y++)
	{
		for (unsigned int x = 0; x < texSize; x++)
		{
			if ((x + y) / 4 % 4 == 1)
			{
				bb3[n++] = 128;
				bb3[n++] = 128;
				bb3[n++] = 128;
			}
			else
			{
				bb3[n++] = 255;
				bb3[n++] = 255;
				bb3[n++] = 255;
			}
		}
	}
	data.push_back(bb3.data());

	std::vector<unsigned int> bb4(texSize * texSize * 3);
	n = 0;
	// Generate some diagonal lines for the second layer
	for (unsigned int y = 0; y < texSize; y++)
	{
		for (unsigned int x = 0; x < texSize; x++)
		{
			if (((x / checkSize + y / checkSize) % 2) == 1)
			{
				bb4[n++] = 0;
				bb4[n++] = 0;
				bb4[n++] = 0;
			}
			else
			{
				bb4[n++] = 255;
				bb4[n++] = 255;
				bb4[n++] = 255;
			}
		}
	}
	data.push_back(bb4.data());


	opts.minFilter = mb::ctes::TextureFilter::Linear;
	opts.magFilter = mb::ctes::TextureFilter::Linear;
	opts.internalFormat = GL_RGB8;
	opts.level = 0;
	opts.format = GL_RGB;
	opts.type = GL_UNSIGNED_BYTE;
	mb::Texture* tex = new mb::Texture2DArray(opts, data, texSize, texSize);

	std::vector<std::pair<const char*, mb::Uniform*> > uniforms;
	uniforms.push_back(std::make_pair("projection", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("view", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("model", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("layer", new mb::Uniform(mb::Float, layer)));
	uniforms.push_back(std::make_pair("tex", new mb::Uniform(mb::TextureSampler, tex)));

	mb::ShaderMaterial material("textureShader", shaders, uniforms);

	mbCube = new mb::Node(std::string("cube"));
	mbCube->setMesh(new mb::MeshRenderer(torus, &material));
	mbCube->addComponent(new SplineMovement());
	mbCube->addComponent(new mb::RotateComponent(mb::Axis::x, 1.0f, true));

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
		mbCube->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::x);
	}
	else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Y))
	{
		mbCube->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::y);
	}
	else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Z))
	{
		mbCube->getComponent<mb::RotateComponent>()->setAxis(mb::Axis::z);
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::Num0))
	{
		mbCube->getMesh()->getMaterial()->uniform("layer")->value(0.0f);
	}
	else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Num1))
	{
		mbCube->getMesh()->getMaterial()->uniform("layer")->value(1.0f);
	}
	else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Num2))
	{
		mbCube->getMesh()->getMaterial()->uniform("layer")->value(2.0f);
	}
	else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Num3))
	{
		mbCube->getMesh()->getMaterial()->uniform("layer")->value(3.0f);
	}
	scene->render(dt);
}
