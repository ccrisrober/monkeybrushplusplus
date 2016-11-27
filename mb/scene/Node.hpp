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
#include "../utils/utils.hpp"

namespace MB
{
	class Node
	{
	public:
		MB_API
		Node(const std::string& name = "Node", const std::string& tag = "Untagged");
		MB_API
		virtual ~Node();
		MB_API
		bool isVisible() const;
		MB_API
		bool hasParent() const;
		MB_API
		Node* parent() const;
		MB_API
		void setParent(Node* p);
		MB_API
		void addChild(Node* child);
		MB_API
		void removeChild(Node* child);
		MB_API
		void removeChild(unsigned int index);
		MB_API
		unsigned int getNumChildren() const;
		MB_API
		unsigned int getNumComponents() const;
		MB_API
		Node* getChild(unsigned int index);
		MB_API
		void removeChildren();
		MB_API
		void removeComponents();
		MB_API
		void addComponent(Component* c);
		MB_API
		void setVisible(const bool flag, const bool applyToChildren = false);
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
		std::vector<MB::Component*> getComponents() const;
		MB_API
		void setMesh(MeshRenderer* mesh);
		MB_API
		MeshRenderer* getMesh() const;
		MB_API
		void traverse(const std::function<void(MB::Node* n)>& f);
		MB_API
		void traverseAncestors(const std::function<void(MB::Node* n)>& f);



		template <typename T>
		void toggleComponent()
		{
			for (auto comp : _components)
			{
				if (typeid(*comp) == typeid(T))
				{
					comp->toggle();
				}
			}
		}
		template <typename T>
		void enableComponent()
		{
			for (auto comp : _components)
			{
				if (typeid(*comp) == typeid(T))
				{
					comp->enable();
				}
			}
		}
		template <class T>
		void disableComponent()
		{
			for (auto comp : _components)
			{
				if (typeid(*comp) == typeid(T))
				{
					comp->disable();
				}
			}
		}
		template <class T>
		bool hasComponent() const
		{
			for (auto comp : _components)
			{
				if (typeid(*comp) == typeid(T))
				{
					return true;
				}
			}
			return false;
		}
		template <class T>
		T* getComponent()
		{
			for (auto comp : _components)
			{
				// std::cout << typeid(*comp).name() << std::endl;
				// std::cout << typeid(T).name() << std::endl;
				if (typeid(*comp) == typeid(T))
				{
					return static_cast<T*>(comp);
				}
			}
			return nullptr;
		}



		MB_API
		Component* getComponentByIndex(unsigned int index);
		MB_API
		friend std::ostream& operator<<(std::ostream & str, const Node& n);
		MB_API
		std::string uuid() const;
		MB_API
		Layer& layer();
	protected:
		MeshRenderer* _mesh = nullptr;
		std::vector<Node*> _children;
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

//template <typename T, bool = std::is_base_of<BaseComponent, T>::value>