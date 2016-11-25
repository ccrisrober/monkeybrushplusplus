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
#include <vector>

MB::Engine* engine;
MB::Scene* scene;

void renderFunc(float dt);

int main(void)
{
    MB::GLContext context(3, 3, 1024, 768, "Hello MB");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene(engine);

	auto camera = new MB::PerspectiveCamera(90.0f, 1.0, 0.01f, 1000.0f);

	camera->setWindowSize(context.getWidth(), context.getHeight());

	auto view = camera->viewMatrix();
	auto proj = camera->projectionMatrix();
	camera->transform().position().set(0.0f, 1.5f, 5.5f);
	camera->transform().rotation().set(0.0f, 1.0f, 0.0f);
	view = camera->viewMatrix();

	MB::Drawable* geom;
	MB::Material* material;
	auto particles = new MB::ParticleSystem(geom, material);

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}
void renderFunc(float)
{
}
