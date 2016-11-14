/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal
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

#ifndef __MB_NODE__
#define __MB_NODE__

#include <vector>
#include <ctime>
#include <regex>
#include "Transform.hpp"

#include "Component.hpp"

namespace MB {
	class Node {
	public:
		Node(const std::string& name = "dummy", const std::string& tag = "SimpleTag")
		: _name(name)
		, _id(_generateUUID())
		, _parent(nullptr)
		, _tag(tag)
		{

		}
		inline bool isEnabled() const
		{
			return this->_isEnabled;
		}
		inline bool hasParent() const
		{
			return this->_parent != nullptr;
		}
		inline Node* parent() const
		{
			return this->_parent;
		}
		void setParent(Node* p)
		{
            // TODO: Check parent in p node (addChild or removeChild in p.parent)
			this->_parent = p;
		}
		void addChild(Node* n)
		{
			if (n == this)
			{
				throw "TODO: ERROR";
			}
			n->setParent(this);
			this->_children.push_back(n);
		}
		void removeChild(Node* n) {
			// TODO
		}
		void addComponent(Component* c)
		{
			c->setNode(this);
			this->_components.push_back(c);
		}
		void setEnabled(const bool v)
		{
			this->_isEnabled = v;
			for(auto& c: this->_children)
			{
				c->setEnabled(v);
			}
		}
		void removeAll() {
            // TODO: Clear Nodes ...
			this->_children.clear( );
		}
		std::vector<Node*> children() const {
			return this->_children;
		}
		std::vector<Component*> components() const {
			return this->_components;
		}
		Transform& transform() {
			return this->_transform;
		}
	private:
		std::string _generateUUID() const
		{
			time_t d = time(0);
			std::string uuid = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
			std::regex vowel_re("/[xy]/g");

			std::string ret = "";
			//std::regex_replace(ret, uuid.begin(), uuid.end(), vowel_re, std::function<void(char) {
			//});
			/* let uuid = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx".replace(/[xy]/g, function(c) {
                let r = (d + Math.random() * 16) % 16 | 0;
                d = Math.floor(d / 16);
                return (c === "x" ? r : (r & 0x3 | 0x8)).toString(16);
            });*/

			return ret;
		}
	protected:
		std::vector<Node*> _children;
		std::vector<Component*> _components;
		Node* _parent;
		std::string _id;
		bool _isEnabled;
		std::string _tag;
		std::string _name;
		Transform _transform;
	};
}

#endif /* __MB_NODE__ */