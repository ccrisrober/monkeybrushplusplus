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

class SubShaderMaterial : public mb::ShaderMaterial
{
public:
	SubShaderMaterial(const std::string& name,
		const std::vector<std::pair<mb::ShaderType, const char*> >& shaders,
		const std::vector<std::pair<const char*, mb::Uniform*> >& uniforms)
		: mb::ShaderMaterial(name, shaders, uniforms)
	{
		this->_program->addSubroutine("Color", GL_FRAGMENT_SHADER);
	}
	virtual void configUse() override
	{
		_program->activeSubprogram("ColorRed", GL_FRAGMENT_SHADER);
	}
};

int main(void)
{
  mb::GLContext context(3, 3, 1024, 768, "Shader Subroutine");

  auto engine = new mb::Engine(&context, false);
  scene = new mb::Scene(engine, new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 8.44f)));

  mb::Mesh* mesh = new mb::Mesh(MB_MODEL_ASSETS + std::string("/suzanne.obj_"));

  std::string vertexShader = "#version 430\n"
	  "in vec3 position;\n"
	  "uniform mat4 proj;"
	  "uniform mat4 view;"
	  "uniform mat4 model;"
	  "void main() {"
	  "	gl_Position = proj * view * model * vec4(position, 1.0);"
	  "}";
  std::string fragmentShader = "#version 430\n"
	  "out vec4 fragColor;"
	  "subroutine vec4 color_t();"
	  "subroutine uniform color_t Color;"

	  "subroutine(color_t)"
	  "vec4 ColorRed() {"
	  "	return vec4(1, 0, 0, 1);"
	  "}"

	  "subroutine(color_t)"
	  "vec4 ColorBlue() {"
	  "	return vec4(0, 0.4, 1, 1);"
	  "}"

	  "subroutine(color_t)"
	  "vec4 ColorYellow() {"
	  "	return vec4(1, 1, 0, 1);"
	  "}"

	  "void main() {"
	  "	fragColor = Color();"
	  "}";

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
  };

  mb::ShaderMaterial material("subroutineExampleMaterial", shaders, uniforms);

  auto mbNode = new mb::Node(std::string("mesh"));
  mbNode->addComponent(new mb::MeshRenderer(mesh, &material));
  mbNode->addComponent(new mb::ChangeTransformationComponent());
  mbNode->addComponent(new mb::MoveComponent());
  mbNode->addComponent(new mb::RotateComponent(mb::Axis::x, 0.75f, true));

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
