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

mb::Scene* scene;

void renderFunc(float dt);

class ChangeToonLevel : public mb::Component
{
public:
  ChangeToonLevel(const float& level)
    : mb::Component()
    , _level(level)
  {}
  virtual void update(const float) override
  {
    if (mb::Input::isKeyClicked(mb::Keyboard::Key::Plus))
    {
      _level += 1.0f;
      getNode()->getMesh()->getMaterial()->uniform("levels")->value(_level);
    }
    if (mb::Input::isKeyClicked(mb::Keyboard::Key::Minus))
    {
      _level -= 1.0f;
      if (_level < 1.0f)
      {
        _level = 1.0f;
      }
      getNode()->getMesh()->getMaterial()->uniform("levels")->value(_level);
    }
  }
protected:
  float _level;
};

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Toon shading");

	auto engine = new mb::Engine(&context, false);
  scene = new mb::Scene(engine, new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 8.44f)));

	mb::Mesh* model = new mb::Mesh(MB_MODEL_ASSETS + std::string("/suzanne.obj_"));

	std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
		{
			mb::VertexShader,
			"#version 330\n"
			"layout(location = 0) in vec3 position;\n"
			"layout(location = 1) in vec3 normal;\n"
			"out vec3 outPosition;\n"
			"out vec3 outNormal;\n"
			"uniform mat4 projection;\n"
			"uniform mat4 view;\n"
			"uniform mat4 model;\n"
			"void main() {\n"
			"   outPosition = vec3(model * vec4(position, 1.0));\n"
			"	  gl_Position = projection * view * vec4(outPosition, 1.0);\n"
			"	  mat3 normalMatrix = mat3(inverse(transpose(model)));\n"
			"	  outNormal = normalize(normalMatrix * normal);\n"
			"}\n"
		},{
			mb::FragmentShader,
			"#version 330\n"
			"in vec3 outPosition;\n"
			"in vec3 outNormal; \n"
			"out vec4 fragColor; \n"
			"uniform sampler2D tex; \n"
			"uniform vec3 viewPos; \n"
			"uniform vec3 color; \n"
			"uniform float levels; \n"
			"void main() {\n"
			"	  float scaleFactor = 1.0 / levels; \n"
			"	  vec3 n = normalize(outNormal); \n"
			" 	vec3 s = normalize(viewPos.xyz - outPosition.xyz); \n"
			"	  vec3 ambient = color * vec3(0.135, 0.2225, 0.1575); \n"
			"	  float cosine = dot(s, n); \n"
			"	  vec3 diffuse = color * floor(cosine * levels) * scaleFactor; \n"
			"	  fragColor = vec4(vec3(ambient + diffuse), 1.0); \n"
			"}\n"
		}
	};

  float levels = 5.0f;

	std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
		std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
		std::make_pair("view", new mb::Uniform(mb::Matrix4)),
		std::make_pair("model", new mb::Uniform(mb::Matrix4)),
		std::make_pair("viewPos", new mb::Uniform(mb::Vector3)),
		std::make_pair("levels", new mb::Uniform(mb::Float, levels)),
		std::make_pair("color", new mb::Uniform(mb::Vector3, mb::Vect3(0.54f, 0.89f, 0.63f)))
	};

  mb::ShaderMaterial material("material", shaders, uniforms);

	auto mbNode = new mb::Node(std::string("model"));
	mbNode->addComponent(mb::ComponentPtr(new mb::MeshRenderer(model, &material)));
	mbNode->addComponent(mb::ComponentPtr(new mb::RotateComponent(mb::Axis::y, 0.15f)));
  mbNode->addComponent(mb::ComponentPtr(new mb::ChangeTransformationComponent()));
  mbNode->addComponent(mb::ComponentPtr(new ChangeToonLevel(levels)));

	mbNode->getComponent<mb::RotateComponent>()->setRotate(true);

	scene->root()->addChild(mb::NodePtr(mbNode));

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
