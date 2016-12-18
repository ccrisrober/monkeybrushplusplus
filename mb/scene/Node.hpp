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
#include "../maths/Sphere3D.hpp"

namespace mb
{
  typedef std::shared_ptr<Node> NodePtr;
	class Node
    : public std::enable_shared_from_this<Node>
	{
	public:
		// Creates GameObject from prefab and adds it to the scene.
		MB_API
		static Node* createFromPrefab(const Node& /*prefab*/)
		{
			// TODO
			/**
			* Clone all components
			* Initialize all components
			*/
			return nullptr;
		}
		Node(const Node&)
		{
			// TODO
		}
		MB_API
    mb::NodePtr findByName(const std::string& name);
		MB_API
    mb::NodePtr findByTag(const std::string& tag);
		MB_API
    mb::NodePtr findById(const std::string uuid);


		MB_API
		Node(const std::string& name/* = "Node"*/, const std::string& tag = "Untagged");
		//MB_API
	  virtual ~Node();
		MB_API
		bool isVisible() const;
		MB_API
		bool hasParent() const;
		MB_API
    mb::NodePtr parent() const;
		MB_API
		void setParent(mb::NodePtr p);
		MB_API
		void addChild(mb::NodePtr child);
		MB_API
		void removeChild(mb::NodePtr child);
		MB_API
		void removeChild(unsigned int index);
		MB_API
		unsigned int getNumChildren() const;
		MB_API
		unsigned int getNumComponents() const;
		MB_API
		mb::NodePtr getChild(unsigned int index);
		MB_API
		void removeChildren();
		MB_API
		void removeComponents();
    MB_API
    void addComponents( std::initializer_list<mb::ComponentPtr> components );
    MB_API
    void addComponent( const mb::ComponentPtr& c );
		MB_API
		void setVisible(const bool flag, const bool applyToChildren = false);
		MB_API
		std::vector<mb::NodePtr> children() const;
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
		std::vector<mb::ComponentPtr> getComponents() const;
		MB_API
		MeshRenderer* getMesh(); // const;
    MB_API
    void traverse( const std::function<void( mb::NodePtr n )>& f );
    MB_API
    void traverseAncestors( const std::function<void( mb::NodePtr n )>& f );

		template <typename T>
		void toggleComponent()
		{
			for (auto comp : _components)
			{
				if (typeid(*comp.get()) == typeid(T))
				{
					comp.get()->toggle();
				}
			}
		}
		template <typename T>
		void enableComponent()
		{
			for (auto comp : _components)
			{
				if (typeid(*comp.get()) == typeid(T))
				{
					comp.get()->enable();
				}
			}
		}
		template <class T>
		void disableComponent()
		{
			for (auto comp : _components)
			{
				if (typeid(*comp.get()) == typeid(T))
				{
					comp.get()->disable();
				}
			}
		}
		template <class T>
		bool hasComponent() const
		{
			for (auto comp : _components)
			{
				if (typeid(*comp.get()) == typeid(T))
				{
					return true;
				}
			}
			return false;
		}
		template <class T>
		T* getComponent();



		MB_API
		mb::ComponentPtr getComponentByIndex(unsigned int index);
		MB_API
		friend std::ostream& operator<<(std::ostream & str, const Node& n);
		MB_API
		std::string uuid() const;
		MB_API
		Layer& layer();
	protected:
		std::vector<mb::NodePtr> _children;
		std::vector<mb::ComponentPtr> _components;

		std::string _name;
		std::string _id;
    mb::NodePtr _parent;
		std::string _tag;
		bool _visible;
		Transform _transform;

		Layer _layer;

	private:
    mb::NodePtr _searchName(const std::string& name, const mb::NodePtr& elem);
    mb::NodePtr _searchTag(const std::string& tag, const mb::NodePtr& elem);
    mb::NodePtr _searchUUID(const std::string& uuid, const mb::NodePtr& elem);
	};
  template<class T>
  T * Node::getComponent()
  {
    {
      for (auto comp : _components)
      {
        // std::cout << typeid(*comp).name() << std::endl;
        // std::cout << typeid(T).name() << std::endl;
        if (typeid(*comp.get()) == typeid(T))
        {
          return static_cast<T*>(comp.get());
        }
      }
      return nullptr;
    }
  }
}

#endif /* __MB_NODE__ */

//template <typename T, bool = std::is_base_of<BaseComponent, T>::value>
