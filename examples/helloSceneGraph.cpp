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

MB::Engine* engine;
MB::Scene* scene;

MB::Cube* cube;
MB::Cylinder* cylinder;
MB::Prism* prism;

void renderFunc(float dt);



/*#include <regex>
#include <map>
#include <string>
std::map<std::string, std::string> trozos;

std::string _processImports(const std::string& src)
{

	std::string s(src);
	std::smatch m;
	std::regex regex(rg, std::tr1::regex_constants::extended);
	while (std::regex_search(s, m, regex))
	{
		std::vector<std::string> vv;
		vv.push_back(*(m.begin() + 1));
		s = m.suffix().str();
		s += trozos[vv[0]];
	}
	

	return s;
}

void trozitos() {
	trozos["prueba"] = "Codigo prueba";
	trozos["prueba2"] = "Codigo prueb2a";

	std::string shader = "#import<prueba>";
	std::string code = _processImports(shader);
	std::cout << code << std::endl;
}*/












int main(void)
{
	//trozitos();
	//MB::LOG::headers = false;
	//MB::LOG::level = MB::LOG::INFO;
	//MB::LOG::date = true;

    MB::GLContext context(3, 3, 1024, 768, "Hello SceneGraph");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene(engine);

	MB::ResourceDrawable::add("capsule", new MB::Capsule(0.5f, 1.0f));

	cube = new MB::Cube(1.0f);
	cylinder = new MB::Cylinder(1.0f, 1.5f, 25, 15);
	prism = new MB::Prism(1.0f, 1.5f, 5);
	MB::ResourceDrawable::add("torus", new MB::Torus(0.5f, 0.25f, 25, 40));

	MB::SimpleShadingMaterial material;
	material.uniform("color")->value(MB::Vect3(MB::Color3::Red));
	MB::NormalMaterial normalMat;

	std::vector<std::pair<MB::ShaderType, const char*> > shaders;
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

	shaders.push_back(std::make_pair(MB::VertexShader, vertexShader));
	shaders.push_back(std::make_pair(MB::FragmentShader, fragmentShader));


	std::vector<std::pair<const char*, MB::Uniform*> > uniforms;
	uniforms.push_back(std::make_pair("projection", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("view", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("model", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("color", new MB::Uniform(MB::Vector3, MB::Vect3::createFromScalar(1.0f))));
	uniforms.push_back(std::make_pair("viewPos", new MB::Uniform(MB::Vector3)));

	MB::ShaderMaterial shaderMat("shaderMat", shaders, uniforms);

	MB::Node* mbCube = new MB::Node(std::string("cube"));
	mbCube->setMesh(new MB::MeshRenderer(cube, MB::MaterialCache::get("shaderMat")));
	mbCube->addComponent(new MB::MoveComponent());
	mbCube->addComponent(new MB::RotateComponent(MB::Axis::x));
	mbCube->transform().position().set(0.0f, 3.15f, -8.98f);
	mbCube->transform().scale().set(2.0f, 2.0f, 1.0f);

	MB::Node* mbPrism = new MB::Node(std::string("prism"));
	mbPrism->setMesh(new MB::MeshRenderer(prism, &normalMat));
	mbPrism->transform().position().set(-0.44f, -2.0f, 2.35f);
	mbPrism->transform().scale().set(0.5f, 0.5f, 1.0f);
	mbCube->addChild(mbPrism);

	MB::Node* mbCapsule = new MB::Node(std::string("capsule"));
	mbCapsule->setMesh(new MB::MeshRenderer(MB::ResourceDrawable::get("capsule"), &normalMat));
	mbCapsule->transform().position().set(-1.44f, -2.5f, 0.87f);
	mbPrism->addChild(mbCapsule);

	MB::Node* mbTorus = new MB::Node(std::string("torus"));
	mbTorus->setMesh(new MB::MeshRenderer("torus", &normalMat));
	mbTorus->transform().position().set(1.1f, -1.91f, -1.08f);
	mbTorus->transform().scale().set(1.0f, 0.5f, 1.0f);
	mbCube->addChild(mbTorus);

	MB::Node* mbCylinder = new MB::Node(std::string("cylinder"));
	mbCylinder->setMesh(new MB::MeshRenderer(cylinder, &material));
	mbCylinder->transform().position().set(1.44f, -2.5f, 0.8f);
	mbCylinder->transform().scale().set(0.5f, 1.0f, 2.0f);
	mbTorus->addChild(mbCylinder);

	std::function<void()> f0([&]() {
		std::cout << "SCENE HAS " << scene->root()->children().size() << " CHILDREN" << std::endl;
	});

	std::function<void()> f1([&]() {
		MB::LOG(MB::LOG::INFO) << "FIRST RENDER FINISHED";
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
	if (MB::Input2::isKeyPressed(MB::Keyboard::Key::Esc))
	{
		engine->close();
		return;
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::Z))
	{
		std::cout << "DEPTH OFF" << std::endl;
		engine->state()->depth.setStatus(false);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::X))
	{
		std::cout << "DEPTH OK" << std::endl;
		engine->state()->depth.setStatus(true);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::K))
	{
		engine->state()->culling.setStatus(false);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::L))
	{
		engine->state()->culling.setStatus(true);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::M))
	{
		engine->state()->setPolygonMode(GL_FILL);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::N))
	{
		engine->state()->setPolygonMode(GL_LINE);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::Num1))
	{
		engine->state()->culling.setFlipSided(GL_CCW);
	}
	if (MB::Input2::isKeyClicked(MB::Keyboard::Key::Num2))
	{
		engine->state()->culling.setFlipSided(GL_CW);
	}
	scene->render(dt);
}
