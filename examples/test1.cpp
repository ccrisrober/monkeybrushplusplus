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

//#include <rapidjson/include/rapidjson/document.h>

mb::Engine* engine;
mb::Scene* scene;

void renderFunc(float dt);

mb::Node* mbMesh;

//using namespace rapidjson;

int main(int argc, const char** argv)
{
	/*std::string sceneFile = std::string(MB_FILES_ASSETS + std::string("/scene.json"));
	std::ifstream file(sceneFile);
	std::stringstream buffer;
	buffer << file.rdbuf();

	Document document;
	document.Parse(buffer.str().c_str());*/

	mb::ArgumentParser parser = mb::ArgumentParser().description("just an example");

	parser.add_option("-f", "--file").dest("filename")
		.help("write report to FILE").metavar("FILE");
	parser.add_option("-q", "--quiet")
		.action("store_false").dest("verbose").set_default("1")
		.help("don't print status messages to stdout");

	parser.print_help();
	parser.print_version();

	mb::Values options = parser.parse_args(argc, argv);
	std::vector<std::string> args = parser.args();
	if (options.get("verbose"))
	{
		std::cout << options["filename"] << std::endl;
	}

	mb::GLContext context(3, 3, 1024, 768, "Hello mb");

	engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::Mesh* mesh = new mb::Mesh(MB_MODEL_ASSETS + std::string("/suzanne.obj_"));

	mb::SimpleShadingMaterial material;
	material.uniform("color")->value(mb::Vect3(mb::Color3::Green));

	mbMesh = new mb::Node(std::string("mesh"));
	mbMesh->setMesh(new mb::MeshRenderer(mesh, &material));
	mbMesh->addComponent(new mb::MoveComponent());
	mbMesh->addComponent(new mb::RotateComponent(mb::Axis::x));


	auto light = mb::LightPtr(new mb::PointLight());

	mb::Layer l;
	mb::Layer l2;
	l.enable(1);	// Sees layer 1 (and default 0) 
	l.set(1);		// Only sees layer 1

	std::cout << mb::LayerLookup::name(1) << std::endl;
	std::cout << mb::LayerLookup::name(2) << std::endl;
	mb::LayerLookup::name("Siniestro", 2);
	std::cout << mb::LayerLookup::name(2) << std::endl;

	/*
	camera.layer.enable( 1 ); // camera now sees default layer 0 and layer 1
	camera.layer.set( 1 ); // camera now sees only layer 1

	mesh.layer.set( 1 ); // mesh is in layer 1*/

	scene->root()->addChild(mbMesh);

	std::string iniFile = std::string(MB_FILES_ASSETS + std::string("/sample.ini"));
	mb::ini::parseIniFile(iniFile);
	std::cout << "MYSQL Host: " << mb::ini::getOptionToString("mysql_host") << "\n"; //Return string
	std::cout << "MYSQL User: " << mb::ini::getOptionToString("mysql_user") << "\n"; //Return string
	std::cout << "MYSQL Pass: " << mb::ini::getOptionToString("mysql_pass") << "\n"; //Return string
	std::cout << "MYSQL DB: " << mb::ini::getOptionToChar("mysql_db") << "\n"; //Return char
	std::cout << "MYSQL Socket: " << mb::ini::getOptionToChar("mysql_socket") << "\n"; //Return char
	std::cout << "MYSQL Port: " << mb::ini::getOptionToInt("mysql_port") << "\n"; //Return int
	std::cout << "Bad Config Item: " << mb::ini::getOptionToString("bad_config_item") << "\n"; //Should return nothing

	// engine->run(renderFunc);

	delete(scene);
	delete(engine);

	return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->camera->update(dt);
	if (mb::Input::isKeyPressed(mb::Keyboard::Key::Esc))
	{
		engine->close();
		return;
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
