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

namespace MB
{
	class Node
	{
	public:
		Node(const std::string& name = "dummy", const std::string& tag = "SimpleTag");
		bool isEnabled() const;
		bool hasParent() const;
		Node* parent() const;
		void setParent(Node* p);
		void addChild(Node* n);
        void removeChild(Node* /*n*/);
		void addComponent(Component* c);
		void setEnabled(const bool v);
		void removeAll();
		std::vector<Node*> children() const;
		std::vector<Component*> components() const;
		Transform& transform();
		void _updateMatrixWorld(bool force = false);

		std::string name() const
		{
			return this->_name;
		}
		std::string tag() const
		{
			return this->_tag;
		}
		void tag(const std::string& t)
		{
			this->_tag = t;
		}
		friend std::ostream& operator<<(std::ostream & str, const Node& n) {
			str << n._name << " => " << n._id;
			return str;
		}
	private:
		std::string _generateUUID() const;
	protected:
		std::vector<Node*> _children;
        std::vector<Component*> _components;
		std::string _name;
		std::string _id;
        Node* _parent;
        std::string _tag;
        bool _isEnabled;
		Transform _transform;
	};
}

#endif /* __MB_NODE__ */
