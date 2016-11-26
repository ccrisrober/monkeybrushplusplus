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

namespace MB
{
	Scene::Scene(Engine* engine)
	: _sceneGraph(new Node())
	, _engine(engine)
	{
	}
	Node* Scene::root() const
	{
		return this->_sceneGraph;
	}
	Node* Scene::findByName(const std::string& name)
	{
		Node* toRet = this->_searchName(name, root());
		return toRet;
	}
	Node* Scene::findByTag(const std::string& tag)
	{
		Node* toRet = this->_searchTag(tag, root());
		return toRet;
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
	Node* Scene::_searchName(const std::string& name, Node* elem)
	{
		if (elem->hasParent() && elem->name() == name) {
			return elem;
		}
		// Search in childrens
		for (auto& c : elem->children())
		{
			auto child = this->_searchName(name, c);
			if (child)
			{
				return child;
			}
		}
		return nullptr;
	}
	Node* Scene::_searchTag(const std::string& tag, Node* elem)
	{
		if (elem->hasParent() && elem->tag() == tag) {
			return elem;
		}
		// Search in childrens
		for (auto& c : elem->children())
		{
			auto child = this->_searchTag(tag, c);
			if (child)
			{
				return child;
			}
		}
		return nullptr;
	}
	void Scene::render(float dt)
	{
		_totalMeshes = 0;
		// Before render functions
		applyQueue(_beforeRender);
		_subUpdate(root(), dt);
		_subrender(root());
		// After render functions
		applyQueue(_afterRender);
	}
	void Scene::_subUpdate(Node* n, float dt)
	{
		if (!n->isVisible())
		{
			return;
		}
		for (const auto& comp : n->getComponents())
		{
			comp->update(dt);
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
			n->_updateMatrixWorld();
			auto model = n->transform().matrixWorld();
			mr->render(model);
			++this->_totalMeshes;
		}
		for (const auto& child : n->children())
		{
			this->_subrender(child);
		}
	}
	void Scene::addLight(MB::Light* light)
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
	std::vector<MB::Light*> Scene::lights() const
	{
		return this->_lights;
	}
}
