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

// TODO: http://gameprogrammingpatterns.com/dirty-flag.html

#include "Scene.hpp"
#include <iostream>
#include "MeshRenderer.hpp"
#include "Engine.hpp"

namespace mb
{
	Scene::Scene(Engine* engine)
	: _sceneGraph(new Node())
	, _engine(engine)
	, _update(true)
	{
	}
	Node* Scene::root() const
	{
		return this->_sceneGraph;
	}
	void Scene::registerBeforeRender(const std::function<void()>& cb, bool recyclable)
	{
		this->_beforeRender.push_back(std::make_pair(cb, recyclable));
	}
	void Scene::registerAfterRender(const std::function<void()>& cb, bool recyclable)
	{
		this->_afterRender.push_back(std::make_pair(cb, recyclable));
	}
	void Scene::applyQueue(std::vector<std::pair<std::function<void()>, bool> >& queue)
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
		_totalMeshes = 0;
		_totalVertices = 0;
		_drawCalls = 0;
		_totalIndices = 0;

		if (!_update)
		{
			return;
		}

		_batch.clear();

		// Before render functions
		applyQueue(_beforeRender);
		_subUpdate(root(), dt);

		/*auto sortCB = ([](Node* i, Node* j)
		{
			if (i->getMesh()->getMaterial() != j->getMesh()->getMaterial())
				return true;
			return false;
			//return i->name().compare(j->name()) < 0;
		});*/

		std::sort(_batch.begin(), _batch.end());// , sortCB);

		// std::cout << _batch.size() << std::endl;

		for (const auto& node : _batch)
		{
			auto mr = node->getMesh();
			//if ((camera->layer().check(n->layer())) && (mr != nullptr))
			//{
			mr->getMaterial()->uniforms()["projection"]->value(_projection);
			mr->getMaterial()->uniforms()["view"]->value(_view);
			if (mr->getMaterial()->hasUniform("viewPos"))
				mr->getMaterial()->uniforms()["viewPos"]->value(this->camera->GetPos());
			mr->render(node->transform().matrixWorld());
			++this->_totalMeshes;
			//}
		}

		//_subrender(root());
		// After render functions
		applyQueue(_afterRender);

		this->_engine->state()->depth.setStatus(true);
		// TODO: DepthWrite = true;
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

		if ((camera->layer().check(n->layer())) && (n->getMesh() != nullptr))
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
		_projection = this->camera->projectionMatrix(this->_engine->context()->getWidth(), this->_engine->context()->getHeight());
		_view = this->camera->viewMatrix();
	}
	void Scene::_subrender(Node* n)
	{
		if (!n->isVisible())
		{
			return;
		}
		auto mr = n->getMesh();
		if ( (camera->layer().check(n->layer())) && (mr != nullptr))
		{
			mr->getMaterial()->uniforms()["projection"]->value(_projection);
			mr->getMaterial()->uniforms()["view"]->value(_view);
			if (mr->getMaterial()->hasUniform("viewPos"))
				mr->getMaterial()->uniforms()["viewPos"]->value(this->camera->GetPos());
			mr->render(n->transform().matrixWorld());
			++this->_totalMeshes;
			this->_totalIndices += mr->getMesh()->indicesLen();
			this->_totalVertices += mr->getMesh()->verticesLen();
		}
		for (const auto& child : n->children())
		{
			this->_subrender(child);
		}
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
