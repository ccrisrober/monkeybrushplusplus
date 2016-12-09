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
      getNode()->getMesh()->getMaterial()->uniform("tess_level")->value(_tessLevel);
    }
    else if (mb::Input::isKeyPressed(mb::Keyboard::Key::Minus))
    {
      _tessLevel -= 0.1f;
      getNode()->getMesh()->getMaterial()->uniform("tess_level")->value(_tessLevel);
    }
  }
protected:
  float _tessLevel;
};

int main(void)
{
	mb::GLContext context(4, 4, 1024, 768, "Triangle tesselation");

  auto engine = new mb::Engine(&context, false);
  scene = new mb::Scene(engine, new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 8.44f)));

	mb::Drawable* model = new mb::Tetrahedron(1.0f);

	std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
		{
			mb::VertexShader,
			"#version 440																		                      \n"
			"layout(location = 0) in vec3 position;												        \n"
			"uniform mat4 projection;															                \n"
			"uniform mat4 view;																	                  \n"
			"uniform mat4 model;																                  \n"
			"void main() {																		                    \n"
			"	gl_Position = projection * view * model * vec4(position, 1.0f);		  \n"
			"}"
		}, {
			mb::TesselationControlShader,
			"#version 440																		                      \n"
			"layout (vertices = 3) out;															              \n"
			"uniform float tess_level;															              \n"
      "#define ID gl_InvocationID															              \n"
			"void main(void) {                                                    \n"
			"    if (ID == 0) {                                                   \n"
			"        gl_TessLevelInner[0] = tess_level;                           \n"
			"        gl_TessLevelOuter[0] = tess_level;                           \n"
			"        gl_TessLevelOuter[1] = tess_level;                           \n"
			"        gl_TessLevelOuter[2] = tess_level;                           \n"
			"    }                                                               	\n"
			"    gl_out[ID].gl_Position = gl_in[ID].gl_Position;     	            \n"
			"}"
		}, {
			mb::TesselationEvaluationShader,
			"#version 440																		                      \n"
			"layout (triangles) in;                                              	\n"
			"void main(void) {                                                    \n"
			"    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +          \n"
			"                  (gl_TessCoord.y * gl_in[1].gl_Position) +          \n"
			"                  (gl_TessCoord.z * gl_in[2].gl_Position);           \n"
			"}"
		}, {
			mb::FragmentShader,
			"#version 440																		                      \n"
			"out vec4 fragColor;																                  \n"
			"uniform vec3 color;																                  \n"
			"void main() {																		                    \n"
			"	fragColor = vec4(color, 1.0);													              \n"
			"}"
		}
	};

  float tess_level = 2.0f;

	std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
		std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
		std::make_pair("view", new mb::Uniform(mb::Matrix4)),
		std::make_pair("model", new mb::Uniform(mb::Matrix4)),
		std::make_pair("color", new mb::Uniform(mb::Vector3, mb::Vect3(mb::Color3::Pink))),
		std::make_pair("tess_level", new mb::Uniform(mb::Float, tess_level))
	};

	mb::ShaderMaterial material("triangleTesselation", shaders, uniforms);
	material.Cull = false;
	material.PolygonMode = GL_LINE;

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
