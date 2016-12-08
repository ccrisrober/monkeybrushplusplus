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

int main(void)
{
  mb::GLContext context(4, 3, 1024, 768, "Texture Swap");

  auto engine = new mb::Engine(&context, false);
  scene = new mb::Scene(engine, new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 8.44f)));

  auto customPP = new mb::CustomPingPong<mb::Texture*>(
	  new mb::Texture2D({}, MB_TEXTURE_ASSETS + std::string("/Dundus_Square.jpg")),
	  new mb::Texture2D({}, MB_TEXTURE_ASSETS + std::string("/matcap.jpg"))
  );

	mb::Cube* model = new mb::Cube(1.0f);

	std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
		{
			mb::VertexShader,
			"#version 330\n"
			"layout(location = 0) in vec3 position;"
			"layout(location = 1) in vec3 normal;"
			"layout(location = 2) in vec2 uv;"
			"out vec3 outNormal;"
			"out vec2 outUV;"
			"uniform mat4 projection;"
			"uniform mat4 view;"
			"uniform mat4 model;"
			"void main() {"
			"   vec3 outPosition = vec3(model * vec4(position, 1.0));"
			"   gl_Position = projection * view * vec4(outPosition, 1.0);"
			"   mat3 normalMatrix = mat3(inverse(transpose(model)));"
			"   outNormal = normalize(normalMatrix * normal);"
			"   outUV = uv;"
			"}"
		}, {
			mb::FragmentShader,
			"#version 330\n"
			"in vec3 outNormal;"
			"in vec2 outUV;"
			"out vec4 fragColor;"
			"uniform vec3 viewPos;"
			"uniform sampler2D tex;"
			"void main() {"
			"   fragColor = vec4(texture(tex, outUV).rgb, 1.0);"
			"}"
		}
	};

  std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
    std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
    std::make_pair("view", new mb::Uniform(mb::Matrix4)),
    std::make_pair("model", new mb::Uniform(mb::Matrix4)),
    std::make_pair("viewPos", new mb::Uniform(mb::Vector3)),
    std::make_pair("tex", new mb::Uniform(mb::TextureSampler, customPP->first()))
  };

  auto material = new mb::ShaderMaterial("textureShader", shaders, uniforms);

  auto mbNode = new mb::Node(std::string("cube"));
  mbNode->addComponent(new mb::MeshRenderer(model, material));
  mbNode->addComponent(new mb::ChangeTransformationComponent());
  mbNode->addComponent(new mb::MoveComponent());
  mbNode->addComponent(new mb::RotateComponent(mb::Axis::x));

  mbNode->getComponent<mb::RotateComponent>()->setRotate(true);

  scene->root()->addChild(mbNode);

  customPP->first()->bind(0);
  mb::setInterval([&]()
  {
    customPP->swap();
    material->uniform("tex")->value(customPP->first());
  }, 1000);

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
