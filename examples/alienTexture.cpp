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
#include <shaderFiles.h>

mb::Scene* scene;

void renderFunc(float dt);

class UpdateBaseFreq : public mb::Component
{
public:
  UpdateBaseFreq(const float& baseFreq)
    : mb::Component()
    , _baseFreq(baseFreq) {}
  virtual void update(const float) override
  {
    if (mb::Input::isKeyPressed(mb::Keyboard::Key::Minus))
    {
      _baseFreq -= 0.1f;
      getNode()->getMesh()->getMaterial()->uniform("base_freq")->value(_baseFreq);
    }
    if (mb::Input::isKeyPressed(mb::Keyboard::Key::Plus))
    {
      _baseFreq += 0.1f;
      getNode()->getMesh()->getMaterial()->uniform("base_freq")->value(_baseFreq);
    }
  }
protected:
  float _baseFreq;
};

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Alien Texture");

	auto engine = new mb::Engine(&context, false);
  scene = new mb::Scene(engine, new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 8.44f)));

	mb::Mesh* mesh = new mb::Mesh(MB_MODEL_ASSETS + std::string("/suzanne.obj_"));

	//mb::ResourceShader::loadShader(std::string("SimpleNoise3D"), MB_SHADERBACKUP_FILES + std::string("/SimpleNoise3D.glsl"));

  std::string vertexShader = mb::os::readFile(MB_SHADER_FILES + std::string("/alienVertex.glsl"));
  std::string fragmentShader = mb::os::readFile(MB_SHADER_FILES + std::string("/alienFrag.glsl"));

	std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
		{
			mb::VertexShader, vertexShader.c_str()
		},
		{
			mb::FragmentShader, fragmentShader.c_str()
		}
	};

  float base_freq = 6.9f;

	std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
		std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
		std::make_pair("view", new mb::Uniform(mb::Matrix4)),
		std::make_pair("model", new mb::Uniform(mb::Matrix4)),
		std::make_pair("viewPos", new mb::Uniform(mb::Vector3)),
		std::make_pair("base_freq", new mb::Uniform(mb::Float, base_freq))
	};

	mb::ShaderMaterial material("alienMaterial", shaders, uniforms);

	auto mbNode = new mb::Node(std::string("mesh"));
	mbNode->addComponent(new mb::MeshRenderer(mesh, &material));
	mbNode->addComponent(new mb::MoveComponent());
	mbNode->addComponent(new mb::RotateComponent(mb::Axis::x));
  mbNode->addComponent(new mb::ChangeTransformationComponent());
  mbNode->addComponent(new UpdateBaseFreq(base_freq));

	scene->root()->addChild(mbNode);

	engine->run(renderFunc);

	delete(scene);
	delete(engine);

	return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->render(dt);
}
