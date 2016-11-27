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

mb::Cube* cube;
mb::Cylinder* cylinder;
mb::Prism* prism;

void renderFunc(float dt);

int main(void)
{
    mb::GLContext context(3, 3, 1024, 768, "Hello SceneGraph");

    engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::ResourceDrawable::add("capsule", new mb::Capsule(0.5f, 1.0f));

	cube = new mb::Cube(1.0f);
	cylinder = new mb::Cylinder(1.0f, 1.5f, 25, 15);
	prism = new mb::Prism(1.0f, 1.5f, 5);
	mb::ResourceDrawable::add("torus", new mb::Torus(0.5f, 0.25f, 25, 40));

	mb::SimpleShadingMaterial material;
	material.uniform("color")->value(mb::Vect3(mb::Color3::Red));
	mb::NormalMaterial normalMat;

	std::vector<std::pair<mb::ShaderType, const char*> > shaders;
	const char* vertexShader =
		"#version 330\n"
		"layout(location = 0) in vec3 position;"
		"layout(location = 1) in vec3 normal;"
		"layout(location = 2) in vec2 texCoord;"
		"out vec3 outPosition;"
		"out vec3 outNormal;"
		"out vec2 outTexCoord;"
		"uniform mat4 projection;"
		"uniform mat4 view;"
		"uniform mat4 model;"
		"void main() {"
		"	outPosition = vec3(model * vec4(position, 1.0));"
		"	gl_Position = projection * view * vec4(outPosition, 1.0);"
		"	mat3 normalMatrix = mat3(inverse(transpose(model)));"
		"	outNormal = normalize(normalMatrix * normal);"
		"	outTexCoord = texCoord;"
		"}";
	const char* fragmentShader =
		"#version 330\n"
		"in vec3 outPosition;"
		"in vec3 outNormal;"
		"in vec2 outTexCoord;"
		"out vec4 fragColor;"
		"uniform vec3 viewPos;"
		"uniform vec3 color;"
		"void main() {"
		"	vec3 N = normalize(outNormal);"
		"	vec3 L = normalize(viewPos - outPosition);"
		"	float dif = dot(N, L);"
		"	dif = clamp(dif, 0.0, 1.0);"
		"	fragColor = vec4(color * dif, 1.0) + vec4(color * 0.1, 1.0);"
		"	fragColor.rgb -= vec3(outTexCoord, 0.0);"
		"}";

	shaders.push_back(std::make_pair(mb::VertexShader, vertexShader));
	shaders.push_back(std::make_pair(mb::FragmentShader, fragmentShader));


	std::vector<std::pair<const char*, mb::Uniform*> > uniforms;
	uniforms.push_back(std::make_pair("projection", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("view", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("model", new mb::Uniform(mb::Matrix4)));
	uniforms.push_back(std::make_pair("color", new mb::Uniform(mb::Vector3, mb::Vect3::createFromScalar(1.0f))));
	uniforms.push_back(std::make_pair("viewPos", new mb::Uniform(mb::Vector3)));

	mb::ShaderMaterial shaderMat("shaderMat", shaders, uniforms);

	mb::Node* mbCube = new mb::Node(std::string("cube"));
	mbCube->setMesh(new mb::MeshRenderer(cube, mb::MaterialCache::get("shaderMat")));
	mbCube->addComponent(new mb::MoveComponent());
	mbCube->addComponent(new mb::RotateComponent(mb::Axis::x));
	mbCube->transform().position().set(0.0f, 3.15f, -8.98f);
	mbCube->transform().scale().set(2.0f, 2.0f, 1.0f);

	mb::Node* mbPrism = new mb::Node(std::string("prism"));
	mbPrism->setMesh(new mb::MeshRenderer(prism, &normalMat));
	mbPrism->transform().position().set(-0.44f, -2.0f, 2.35f);
	mbPrism->transform().scale().set(0.5f, 0.5f, 1.0f);
	mbCube->addChild(mbPrism);

	mb::Node* mbCapsule = new mb::Node(std::string("capsule"));
	mbCapsule->setMesh(new mb::MeshRenderer(mb::ResourceDrawable::get("capsule"), &normalMat));
	mbCapsule->transform().position().set(-1.44f, -2.5f, 0.87f);
	mbPrism->addChild(mbCapsule);

	mbPrism->layer().set(2);

	mb::Node* mbTorus = new mb::Node(std::string("torus"));
	mbTorus->setMesh(new mb::MeshRenderer("torus", &normalMat));
	mbTorus->transform().position().set(1.1f, -1.91f, -1.08f);
	mbTorus->transform().scale().set(1.0f, 0.5f, 1.0f);
	mbCube->addChild(mbTorus);

	mbTorus->layer().set(2);

	mb::Node* mbCylinder = new mb::Node(std::string("cylinder"));
	mbCylinder->setMesh(new mb::MeshRenderer(cylinder, &material));
	mbCylinder->transform().position().set(1.44f, -2.5f, 0.8f);
	mbCylinder->transform().scale().set(0.5f, 1.0f, 2.0f);
	mbTorus->addChild(mbCylinder);

	std::function<void()> f0([&]() {
		std::cout << "SCENE HAS " << scene->root()->children().size() << " CHILDREN" << std::endl;
	});

	std::function<void()> f1([&]() {
		mb::LOG(mb::LOG::INFO) << "FIRST RENDER FINISHED";
	});

	scene->registerBeforeRender(f0);
	scene->registerAfterRender(f1);

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
	if (mb::Input2::isKeyClicked(mb::Keyboard::Key::C))
	{
		scene->camera->layer().toggle(2);
	}
	if (mb::Input2::isKeyPressed(mb::Keyboard::Key::Esc))
	{
		engine->close();
		return;
	}
	if (mb::Input2::isKeyClicked(mb::Keyboard::Key::Z))
	{
		std::cout << "DEPTH OFF" << std::endl;
		engine->state()->depth.setStatus(false);
	}
	if (mb::Input2::isKeyClicked(mb::Keyboard::Key::X))
	{
		std::cout << "DEPTH OK" << std::endl;
		engine->state()->depth.setStatus(true);
	}
	if (mb::Input2::isKeyClicked(mb::Keyboard::Key::K))
	{
		engine->state()->culling.setStatus(false);
	}
	if (mb::Input2::isKeyClicked(mb::Keyboard::Key::L))
	{
		engine->state()->culling.setStatus(true);
	}
	if (mb::Input2::isKeyClicked(mb::Keyboard::Key::M))
	{
		engine->state()->setPolygonMode(GL_FILL);
	}
	if (mb::Input2::isKeyClicked(mb::Keyboard::Key::N))
	{
		engine->state()->setPolygonMode(GL_LINE);
	}
	if (mb::Input2::isKeyClicked(mb::Keyboard::Key::Num1))
	{
		engine->state()->culling.setFlipSided(GL_CCW);
	}
	if (mb::Input2::isKeyClicked(mb::Keyboard::Key::Num2))
	{
		engine->state()->culling.setFlipSided(GL_CW);
	}
	scene->render(dt);
}
