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
    mb::GLContext context(4, 3, 1024, 768, "Spherical Harmonics");

    auto engine = new mb::Engine(&context, false);
    scene = new mb::Scene(engine, new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 8.44f)));

	  mb::Mesh* mesh = new mb::Mesh(MB_MODEL_ASSETS + std::string("/suzanne.obj_"));

	  std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
		  {
			  mb::VertexShader,
			  "#version 430\n"
			  "layout(location = 0) in vec3 position;"
			  "layout(location = 1) in vec3 normal;"
			  "out vec3 outPosition;"
			  "out vec3 outNormal;"

			  "uniform mat4 projection;"
			  "uniform mat4 view;"
			  "uniform mat4 model;"

			  "void main() {"
			  "	outPosition = vec3(model * vec4(position, 1.0));"
			  "	gl_Position = projection * view * vec4(outPosition, 1.0);"
			  "	mat3 normalMatrix = mat3(inverse(transpose(model)));"
			  "	outNormal = normalize(normalMatrix * normal);"
			  "}"
		  }, {
			  mb::FragmentShader,
			  "#version 430\n"
			  "in vec3 outPosition;"
			  "in vec3 outNormal;"
	          "out vec4 fragColor;"
	          "const float invGamma = 1.0/2.2;"
	          "const mat4 mSH_R =mat4( 0.0151426, 0.0441249, -0.0200723, "
	    	  "0.040842, 0.0441249, -0.0151426, 0.0147908, 0.161876, -0.0200723, "
	    	  "0.0147908, 0.0476559, 0.016715, 0.040842, 0.161876, 0.016715, 0.394388);"
	          "const mat4 mSH_G =mat4( 0.0158047, -0.0553513, -0.0183098, -0.0649404, "
	    	  "-0.0553513, -0.0158047, 0.0294534, 0.147578, -0.0183098, 0.0294534, -0.0211293, "
	    	  "0.030445, -0.0649404, 0.147578, 0.030445, 0.381122);"
	          "const mat4 mSH_B =mat4( -0.00060538, -0.143711, -0.0279153, -0.15276, -0.143711, "
	          "0.00060538, 0.0364631, 0.183909, -0.0279153, 0.0364631, -0.0566425, 0.0386598, -0.15276, "
	          "0.183909, 0.0386598, 0.419227);"
	          "void main()"
	          "{"
	          "    vec4 nor = vec4(normalize(outNormal),1.0);"
	          "    vec3 col;"
	          "    col.x = dot(nor, (mSH_R * nor));"
	          "    col.y = dot(nor, (mSH_G * nor));"
	          "    col.z = dot(nor, (mSH_B * nor));"
	          "    //Gamma correction\n"
	          "    fragColor = vec4(pow(col.xyz, vec3(invGamma)),1.0);"
	          "}"
	      }
	  };

	  std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
		  std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
		  std::make_pair("view", new mb::Uniform(mb::Matrix4)),
		  std::make_pair("model", new mb::Uniform(mb::Matrix4))
	  };

	  mb::ShaderMaterial material("shMaterial", shaders, uniforms);

	  auto mbNode = new mb::Node(std::string("mesh"));
    mbNode->addComponent(new mb::MeshRenderer(mesh, &material));
    mbNode->addComponent(new mb::MoveComponent());
    mbNode->addComponent(new mb::RotateComponent(mb::Axis::x, 1.0f, true));
    mbNode->addComponent(new mb::ChangeTransformationComponent());

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
