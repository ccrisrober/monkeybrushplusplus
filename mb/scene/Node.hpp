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

#ifndef __MB_NODE__
#define __MB_NODE__

#include <mb/api.h>

#include <vector>
#include <unordered_map>
#include <ctime>
#include <regex>
#include "Transform.hpp"
#include <algorithm>

#include "Component.hpp"

namespace MB
{
	class Node
	{
	public:
		MB_API
		Node(const std::string& name = "Node", const std::string& tag = "Untagged");
		MB_API
		bool isEnabled() const;
		MB_API
		bool hasParent() const;
		MB_API
		Node* parent() const;
		MB_API
		void setParent(Node* p);
		MB_API
		void addChild(Node* n);
		MB_API
		void removeChild(Node* n);
		MB_API
		void removeChild(unsigned int index);
		MB_API
		void addComponent(Component* c);
		MB_API
		void setEnabled(const bool v);
		MB_API
		void removeAll();
		MB_API
		std::vector<Node*> children() const;
		MB_API
		Transform& transform();
		MB_API
		void _updateMatrixWorld(bool force = false);
		MB_API
		std::string name() const;
		MB_API
		std::string tag() const;
		MB_API
		void name(const std::string& n);
		MB_API
		void tag(const std::string& t);

		template<typename ComponentType>
		MB_API
		ComponentType* getComponent();
		MB_API
		std::vector<MB::Component*> getComponents();

		MB_API
			friend std::ostream& operator<<(std::ostream & str, const Node& n) {
			str << n._name << " => " << n._id;
			return str;
		}
	private:
		std::string _generateUUID() const;
	protected:
		std::vector<Node*> _children;
		std::unordered_map<const std::type_info*, MB::Component*> _components;

		std::string _name;
		std::string _id;
        Node* _parent;
        std::string _tag;
        bool _isEnabled;
		Transform _transform;
	};
}

#endif /* __MB_NODE__ */
