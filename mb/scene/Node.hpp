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

#include "../core/Layer.hpp"

#include "Component.hpp"
#include "MeshRenderer.hpp"

namespace MB
{
	class Node
	{
	public:
		MB_API
		Node(const std::string& name = "Node", const std::string& tag = "Untagged");
		MB_API
		bool isVisible() const;
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
		void setVisible(const bool flag, const bool applyToChildren = false);
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

		MB_API
		void setMesh(MeshRenderer* mesh)
		{
			this->_mesh = mesh;
		}
		MeshRenderer* getMesh() const
		{
			return this->_mesh;
		}
		MB_API
		void traverse(const std::function<void(MB::Node* n)>& f)
		{
			f(this);
			for (auto& child: _children)
			{
				child->traverse(f);
			}
		}
		template <typename T>
		//template <typename T, bool = std::is_base_of<BaseComponent, T>::value>
		T* getComponent()
		{
			for (auto comp : _components)
			{
				std::cout << typeid(*comp).name() << std::endl;
				std::cout << typeid(T).name() << std::endl;
				if (typeid(*comp) == typeid(T))
				{
					return static_cast<T*>(comp);
				}
			}
			return nullptr;
		}
		MB_API
		std::vector<MB::Component*> getComponents() const;
		MB_API
		Component* getComponentByIndex(unsigned int index)
		{
			if (index >= _components.size())
			{
				throw "Component dont found";
			}
			return _components.at(index);
		}

		MB_API
			friend std::ostream& operator<<(std::ostream & str, const Node& n) {
			str << n._name << " => " << n._id;
			return str;
		}

		MB_API
		std::string uuid() const
		{
			return _id;
		}
		Layer& layer()
		{
			return _layer;
		}
	private:
		std::string _generateUUID() const;
	protected:
		MeshRenderer* _mesh = nullptr;
		std::vector<Node*> _children;
		//std::unordered_map<const std::type_info*, MB::Component*> _components;
		std::vector<MB::Component*> _components;

		std::string _name;
		std::string _id;
        Node* _parent;
        std::string _tag;
        bool _visible;
		Transform _transform;

		Layer _layer;
	};
}

#endif /* __MB_NODE__ */
