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
#include <shaderFiles.h>

mb::Engine* engine;
mb::Scene* scene;

void renderFunc(float dt);

class ChangeTessLevelComponent : public mb::Component
{
public:
  ChangeTessLevelComponent(const float& tessLevel)
    : mb::Component()
    , _tessLevel(tessLevel)
  {
  }
  virtual void update(const float) override
  {
    if (mb::Input::isKeyPressed(mb::Keyboard::Key::Plus))
    {
      _tessLevel += 0.1f;
      getNode()->getMesh()->getMaterial()->uniform("uTessLevels")->value(_tessLevel);
    }
    else if (mb::Input::isKeyPressed(mb::Keyboard::Key::Minus))
    {
      _tessLevel -= 0.1f;
      getNode()->getMesh()->getMaterial()->uniform("uTessLevels")->value(_tessLevel);
    }
  }
protected:
  float _tessLevel;
};

int main(void)
{
	mb::GLContext context(4, 4, 1024, 768, "Pong tesselation");

	auto engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine, new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 8.44f)));

	mb::Drawable* model = new mb::Cube(2.0f);

	std::string vertexShader = mb::os::readFile(MB_SHADER_FILES + std::string("/phongVertex.glsl"));
	std::string tessControlShader = mb::os::readFile(MB_SHADER_FILES + std::string("/phongTessControl.glsl"));
	std::string tessEvalShader = mb::os::readFile(MB_SHADER_FILES + std::string("/phongTessEval.glsl"));
	std::string fragmentShader = mb::os::readFile(MB_SHADER_FILES + std::string("/phongFragment.glsl"));

	std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
		{
			mb::VertexShader,
			vertexShader.c_str()
		}, {
			mb::TesselationControlShader,
			tessControlShader.c_str()
		}, {
			mb::TesselationEvaluationShader,
			tessEvalShader.c_str()
		}, {
			mb::FragmentShader,
			fragmentShader.c_str()
		}
	};

  float tess_level = 2.0f;

	std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
		std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
		std::make_pair("view", new mb::Uniform(mb::Matrix4)),
		std::make_pair("model", new mb::Uniform(mb::Matrix4)),
		std::make_pair("color", new mb::Uniform(mb::Vector3, mb::Vect3(mb::Color3::Pink))),
		std::make_pair("uTessLevels", new mb::Uniform(mb::Float, tess_level)),
		std::make_pair("uTessAlpha", new mb::Uniform(mb::Float, 1.0f)),
		std::make_pair("viewPos", new mb::Uniform(mb::Vector3)),
	};

	mb::ShaderMaterial material("triangleTesselation", shaders, uniforms);
	//material.Cull = false;
	//material.PolygonMode = GL_LINE;

	auto mbModel = new mb::Node(std::string("model"));
	// Same as MeshRenderer(model, &material, GL_PATCHES)
	mbModel->addComponent(new mb::MeshRendererTesselation(model, &material));
	//mbModel->addComponent(new mb::MeshRenderer(model, &material, GL_PATCHES));
	mbModel->addComponent(new mb::ChangeTransformationComponent());
	mbModel->addComponent(new mb::MoveComponent());
	mbModel->addComponent(new mb::ChangeTransformationComponent());
	mbModel->addComponent(new ChangeTessLevelComponent(tess_level));

	scene->root()->addChild(mbModel);

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
