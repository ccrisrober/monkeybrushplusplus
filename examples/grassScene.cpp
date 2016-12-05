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

#define MAXPOINTS 500		// Change this to increment num of points
#define RANDOM_POINT 0.02

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Grass Scene");

    engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	srand(time(nullptr));
	float points[MAXPOINTS * 3 / 2];
	float points2[MAXPOINTS * 3 / 2];
	for (int i = 0; i < MAXPOINTS * 3 / 2; i += 3) {
		points[i] = ((float)(std::rand() % 1000)) * RANDOM_POINT;
		points[i + 1] = ((float)(std::rand() % 1000)) * RANDOM_POINT;
		points[i + 2] = ((float)(std::rand() % 1000)) * RANDOM_POINT;

		points2[i] = ((float)(std::rand() % 1000)) * RANDOM_POINT;
		points2[i + 1] = ((float)(std::rand() % 1000)) * RANDOM_POINT;
		points2[i + 2] = ((float)(std::rand() % 1000)) * RANDOM_POINT;
	}

	mb::Cube* model = new mb::Cube(1.0f);

	mb::SimpleShadingMaterial material;
	material.uniform("color")->value(mb::Vect3(mb::Color3::Yellow));

	mb::TexOptions opts;
	opts.wrapS = opts.wrapT = mb::ctes::WrapMode::Clamp2Edge;
	opts.minFilter = opts.magFilter = mb::ctes::TextureFilter::Nearest;
	opts.internalFormat = GL_RGBA;
	opts.format = GL_RGBA;
	opts.type = GL_UNSIGNED_BYTE;
	mb::Texture* tex1 = new mb::Texture2D(opts, "butterfly.png");
	mb::Texture* tex2 = new mb::Texture2D(opts, "dragonfly.png");

	mb::Node* mbModel = new mb::Node(std::string("model"));
	mbModel->setMesh(new mb::MeshRenderer(model, &material));
	
	scene->root()->addChild(mbModel);

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->mainCamera->update(dt);
	scene->render(dt);
}
