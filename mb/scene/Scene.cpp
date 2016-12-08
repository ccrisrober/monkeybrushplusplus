/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 * <https://github.com/maldicion069/monkeybrushplusplus>
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

// TODO: http://gameprogrammingpatterns.com/dirty-flag.html

#include "Scene.hpp"
#include <iostream>
#include "MeshRenderer.hpp"
#include "Engine.hpp"


#include "../materials/ShaderMaterial.hpp"
#include <typeindex>
#include <typeinfo>
#include <vector>
#include <algorithm>
#include <iostream>

namespace mb
{
	Scene::Scene(Engine* engine, SimpleCamera* camera)
	: _sceneGraph(new Node())
	, _engine(engine)
	, _update(true)
	{
		mainCamera = camera;
	}
  Scene::~Scene()
  {
    delete _sceneGraph;
  }
	Node* Scene::root() const
	{
		return this->_sceneGraph;
	}
	void Scene::registerBeforeRender(const std::function<void()>& cb,
    bool recyclable)
	{
		this->_beforeRender.push_back(std::make_pair(cb, recyclable));
	}
	void Scene::registerAfterRender(const std::function<void()>& cb,
    bool recyclable)
	{
		this->_afterRender.push_back(std::make_pair(cb, recyclable));
	}
	void Scene::applyQueue(std::vector<std::pair<std::function<void()>,
    bool> >& queue)
	{
		auto i = std::begin(queue);
		while (i != std::end(queue))
		{
			i->first();
			if (i->second == false)
			{
				i = queue.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
	void Scene::render(float dt)
	{
		profiler.reset();

		if (!_update)
		{
			return;
		}

		_batch.clear();

		// Before render functions
		applyQueue(_beforeRender);
		_subUpdate(root(), dt);

    mainCamera->update(dt);

    if (sort) {
			std::sort(_batch.begin(), _batch.end(), [](Node* mm1, Node* mm2)
			{
				Material *m1 = mm1->getMesh()->getMaterial();
				Material *m2 = mm2->getMesh()->getMaterial();
				static auto smType = std::type_index(typeid(mb::ShaderMaterial));

				auto type1 = std::type_index(typeid(*m1));
				auto type2 = std::type_index(typeid(*m2));

				if (type1 == type2)
				{
					if (
						(type1 == smType)
						&&
						(type2 == smType)
						)
					{
						mb::ShaderMaterial* sm1 = dynamic_cast<mb::ShaderMaterial*>(m1);
						mb::ShaderMaterial* sm2 = dynamic_cast<mb::ShaderMaterial*>(m2);

						if (sm1->name() != sm2->name())
						{
							return sm1->name() < sm2->name();
						}
					}

					VertexArray* v1 = mm1->getMesh()->getMesh()->vertexArray();
					VertexArray* v2 = mm2->getMesh()->getMesh()->vertexArray();

					return v1->handler() < v2->handler();
				}
				return type1 < type2;
			});
		}
		for (const auto& node : _batch)
		{
			auto mr = node->getMesh();
			mr->getMaterial()->uniforms()["projection"]->value(_projection);
			mr->getMaterial()->uniforms()["view"]->value(_view);
			if (mr->getMaterial()->hasUniform("viewPos"))
				mr->getMaterial()->uniform("viewPos")->value(this->mainCamera->GetPos());
			mr->render();
			++profiler.totalMeshes;
			profiler.totalIndices += mr->getMesh()->indicesLen();
			profiler.totalVertices += mr->getMesh()->verticesLen();
		}

		// After render functions
		applyQueue(_afterRender);

		// Restore state
		this->_engine->state()->depth.setStatus(true);
		this->_engine->state()->depth.setMask(true);
	}
	void Scene::_subUpdate(Node* n, float dt)
	{
		if (!n->isVisible())
		{
			return;
		}
		for (const auto& comp : n->getComponents())
		{
			if (comp->isEnabled())
			{
				comp->update(dt);
			}
		}
		n->_updateMatrixWorld();

		if ((mainCamera->layer().check(n->layer())) && (n->getMesh() != nullptr))
		{
			_batch.push_back(n);
		}
		updateCamera();
		for (const auto& child : n->children())
		{
			this->_subUpdate(child, dt);
		}
	}
	void Scene::updateCamera()
	{
		_projection = this->mainCamera->projectionMatrix(
      this->_engine->context()->getWidth(),
      this->_engine->context()->getHeight());
		_view = this->mainCamera->viewMatrix();
	}
	void Scene::addLight(mb::Light* light)
	{
		for (const auto& l : _lights)
		{
			if (l == light)
			{
				return;
			}
		}
		_lights.push_back(light);
	}
	std::vector<mb::Light*> Scene::lights() const
	{
		return this->_lights;
	}
	bool Scene::update() const
	{
		return _update;
	}
	void Scene::update(const bool upd)
	{
		_update = upd;
	}
}
