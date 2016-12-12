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

mb::Scene* scene;

void renderFunc(float dt);

mb::Program program;
mb::Drawable* model;

class BufferGeometry
{
public:
	std::map<std::string, mb::BufferAttribute*> data;
	std::map<std::string, mb::VertexBuffer*> buffers;
	std::vector<unsigned int> indices;
};

BufferGeometry geometry;

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Hello MonkeyBrush");

	auto engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine, new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 8.44f)));

	model = new mb::Cube(1.0f);

	float side = 1.0f;
	float side2 = side / 2.0f;
	geometry.buffers["position"] = new mb::VertexBuffer(GL_ARRAY_BUFFER);
	geometry.data["position"] = new mb::BufferAttribute(
		// Vertices
	{
		// Front
		-side2, -side2, side2,
		side2, -side2, side2,
		side2,  side2, side2,
		-side2,  side2, side2,
		// Right
		side2, -side2, side2,
		side2, -side2, -side2,
		side2,  side2, -side2,
		side2,  side2, side2,
		// Back
		-side2, -side2, -side2,
		-side2,  side2, -side2,
		side2,  side2, -side2,
		side2, -side2, -side2,
		// Left
		-side2, -side2, side2,
		-side2,  side2, side2,
		-side2,  side2, -side2,
		-side2, -side2, -side2,
		// Bottom
		-side2, -side2, side2,
		-side2, -side2, -side2,
		side2, -side2, -side2,
		side2, -side2, side2,
		// Top
		-side2,  side2, side2,
		side2,  side2, side2,
		side2,  side2, -side2,
		-side2,  side2, -side2
	}, 3);
	geometry.indices = {
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};
	mb::VertexBuffer vb = *geometry.buffers["position"];
	vb.data(geometry.data["position"]->array(), GL_STATIC_DRAW);

	program.loadVertexShaderFromText("#version 330\n"
		"in vec3 position;\n"
		"uniform mat4 proj;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"void main() {\n"
		"	gl_Position = proj * view * model * vec4(position, 1.0);\n"
		"}\n"
	);
	program.loadFragmentShaderFromText("#version 330\n"
		"out vec4 fragColor;\n"
		"void main() {\n"
		"	fragColor = vec4(1.0);\n"
		"}\n");
	program.compileAndLink();
	program.autocatching(true, true);

	auto attrs = program.attributes();

	engine->run(renderFunc);

	delete(scene);
	delete(engine);

	return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->mainCamera->update(dt);
	program.use();
	mb::Mat4 proj = scene->mainCamera->projectionMatrix(1024, 768);
	mb::Mat4 view = scene->mainCamera->viewMatrix();
	program.sendUniform4m("proj", proj._values.data());
	program.sendUniform4m("view", view._values.data());
	program.sendUniform4m("model", mb::Mat4()._values);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);

	mb::VertexBuffer vb = *geometry.buffers["position"];
	vb.vertexAttribPointer(0, 3, GL_FLOAT, false);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model->vertexArray()->bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model->vertexArray()->unbind();
	program.unuse();
}
