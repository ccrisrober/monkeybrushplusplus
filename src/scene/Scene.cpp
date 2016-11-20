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

#include "Scene.hpp"
#include <iostream>
#include "MeshRenderer.hpp"

namespace MB
{
	Scene::Scene()
	: _sceneGraph(new Node())
	{
	}
	void Scene::render(float dt)
	{
		_totalMeshes = 0;
		// Before render functions
		applyQueue(_beforeRender);
		for (const auto& child : this->_sceneGraph->children())
		{
			this->_subrender(child, dt);
		}
		// After render functions
		applyQueue(_afterRender);
	}
	Node* Scene::root() const
	{
		return this->_sceneGraph;
	}
	void Scene::_subrender(Node* n, float dt)
	{
		for (const auto& child : n->children())
		{
			this->_subrender(child, dt);
		}
		for (const auto& comp : n->components())
		{
			comp->update(dt);
			if (dynamic_cast<MeshRenderer*>(comp))
			{
				auto mr = (MeshRenderer*)comp;
				mr->getMaterial()->uniforms()["projection"]->value(this->camera->projectionMatrix(500, 500));
				mr->getMaterial()->uniforms()["view"]->value(this->camera->viewMatrix());
				mr->getMaterial()->uniforms()["viewPos"]->value(this->camera->GetPos());
				mr->render();
				++this->_totalMeshes;
			}
		}
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
}
