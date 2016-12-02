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

#include "Node.hpp"

namespace mb
{
	Node::Node(const std::string& name, const std::string& tag)
		: _name(name)
		, _id(mb::utils::generateUUID())
		, _parent(nullptr)
		, _tag(tag)
		, _visible(true)
		, _transform(Transform())
	{
	}
	Node::~Node()
	{
		removeChildren();
		removeComponents();
	}
	bool Node::isVisible() const
	{
		return this->_visible;
	}
	bool Node::hasParent() const
	{
		return this->_parent != nullptr;
	}
	Node* Node::parent() const
	{
		return this->_parent;
	}
	void Node::setParent(Node* p)
	{
		// TODO: Check parent in p node (addChild or removeChild in p.parent)
		this->_parent = p;
	}
	Node* Node::findByName(const std::string& name)
	{
		Node* toRet = this->_searchName(name, this);
		return toRet;
	}
	Node* Node::findByTag(const std::string& tag)
	{
		Node* toRet = this->_searchTag(tag, this);
		return toRet;
	}
	Node* Node::findById(const std::string uuid)
	{
		Node* toRet = this->_searchUUID(uuid, this);
		return toRet;
	}
	Node* Node::_searchName(const std::string& name, Node* elem)
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
	Node* Node::_searchTag(const std::string& tag, Node* elem)
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
	Node* Node::_searchUUID(const std::string& uuid, Node* elem)
	{
		if (elem->hasParent() && elem->uuid() == uuid) {
			return elem;
		}
		// Search in childrens
		for (auto& c : elem->children())
		{
			auto child = this->_searchUUID(uuid, c);
			if (child)
			{
				return child;
			}
		}
		return nullptr;
	}
	void Node::addChild(Node* child)
	{
		if (child == this)
		{
			throw "TODO: ERROR";
		}
		if (std::find(_children.begin(), _children.end(), child) == _children.end())
		{
			child->setParent(this);
			this->_children.push_back(child);
		}
	}
	void Node::removeChild(Node* child) {
		auto it = std::find(_children.begin(), _children.end(), child);
		if (it != _children.end())
		{
			_children.erase(it);
		}
		child->_parent = nullptr;
	}
	void Node::removeChild(unsigned int index)
	{
		_children.erase(_children.begin() + index);
	}
	unsigned int Node::getNumChildren() const
	{
		return _children.size();
	}
	unsigned int Node::getNumComponents() const
	{
		return _components.size();
	}
	Node* Node::getChild(unsigned int index)
	{
		if (index >= _children.size())
		{
			throw "Children dont found";
		}
		return _children.at(index);
	}
	void Node::removeChildren()
	{
		std::for_each(_children.begin(), _children.end(), mb::utils::deleter<Node>());
		_children.clear();
	}
	void Node::removeComponents()
	{
		std::for_each(_components.begin(), _components.end(), mb::utils::deleter<Component>());
		_components.clear();
	}
	void Node::addComponent(Component* c)
	{
		// TODO: http://gamedev.stackexchange.com/questions/55950/entity-component-systems-with-c-accessing-components
		//this->_components[&typeid(*c)] = c;
		if (std::find(_components.begin(), _components.end(), c) == _components.end())
		{
			c->setNode(this);
			c->start();
			this->_components.push_back(c);
		}
	}
	void Node::setVisible(const bool flag, const bool applyToChildren)
	{
		this->_visible = flag;
		if (applyToChildren)
		{
			for (auto& c : this->_children)
			{
				c->setVisible(flag, applyToChildren);
			}
		}
	}
	std::vector<Node*> Node::children() const
	{
		return this->_children;
	}
	Transform& Node::transform()
	{
		return this->_transform;
	}
	void Node::_updateMatrixWorld(bool force)
	{
		if (this->_transform._autoUpdate)
		{
			this->_transform.updateMatrix();
		}
		if (this->_transform._matrixWorldNeedUpdate || force)
		{
			if (!hasParent())
			{
				this->transform()._matrixWorld = this->transform().matrix();
			}
			else
			{
				this->transform()._matrixWorld = Mat4::mult2(this->_parent->transform().matrixWorld(), this->transform().matrix());
				//this->_parent->transform()._matrixWorld.mult(this.transform._matrix, this.transform._matrixWorld);
			}

			this->_transform._matrixWorldNeedUpdate = false;
			force = true;
		}

		for (auto& child : _children)
		{
			child->_updateMatrixWorld(force);
		}
	}
	std::string Node::name() const
	{
		return this->_name;
	}
	void Node::name(const std::string& n)
	{
		_name = n;
	}
	std::string Node::tag() const
	{
		return this->_tag;
	}
	void Node::tag(const std::string& t)
	{
		this->_tag = t;
	}
	std::vector<mb::Component*> Node::getComponents() const
	{
		return _components;
	}
	void Node::setMesh(MeshRenderer* mesh)
	{
		this->_mesh = mesh;
	}
	MeshRenderer* Node::getMesh() const
	{
		return this->_mesh;
	}
	void Node::traverse(const std::function<void(mb::Node* n)>& f)
	{
		f(this);
		for (auto& child : _children)
		{
			child->traverse(f);
		}
	}
	void Node::traverseAncestors(const std::function<void(mb::Node* n)>& f)
	{
		if (this->_parent != nullptr)
		{
			f(this);
			this->_parent->traverseAncestors(f);
		}
	}
	Component* Node::getComponentByIndex(unsigned int index)
	{
		if (index >= _components.size())
		{
			throw "Component dont found";
		}
		return _components.at(index);
	}
	std::ostream& operator<<(std::ostream & str, const Node& n)
	{
		str << n._name << " => " << n._id;
		return str;
	}
	std::string Node::uuid() const
	{
		return _id;
	}
	Layer& Node::layer()
	{
		return _layer;
	}
}