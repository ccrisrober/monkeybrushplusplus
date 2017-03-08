/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 *    <https://github.com/maldicion069/monkeybrushplusplus>
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

#include "components/Component.hpp"
#include "components/MeshRenderer.hpp"
#include "../utils/utils.hpp"
#include "../maths/Sphere3D.hpp"


#include <typeindex>
#include <typeinfo>
#include "../materials/ShaderMaterial.hpp"

namespace mb
{
  typedef std::shared_ptr<Node> NodePtr;
	class Node
    : public std::enable_shared_from_this<Node>
	{
	public:
		MB_API
		static bool node_comparison(NodePtr& node1, NodePtr& node2)
		{
			MaterialPtr m1 = node1->getMesh()->getMaterial();
			MaterialPtr m2 = node2->getMesh()->getMaterial();
			static auto smType = std::type_index(typeid(mb::ShaderMaterial));

			auto type1 = std::type_index(typeid(*m1));
			auto type2 = std::type_index(typeid(*m2));

			if (type1 == type2)
			{
				if (
					(type1 == smType)
					&&
					(type2 == smType)
					)
				{
					mb::ShaderMaterial* sm1 = dynamic_cast<mb::ShaderMaterial*>(m1.get());
					mb::ShaderMaterial* sm2 = dynamic_cast<mb::ShaderMaterial*>(m2.get());

					if (sm1->name() != sm2->name())
					{
						return sm1->name() < sm2->name();
					}
				}

				VertexArray* v1 = node1->getMesh()->getMesh()->vertexArray();
				VertexArray* v2 = node2->getMesh()->getMesh()->vertexArray();

				return v1->handler() < v2->handler();
			}
			return type1 < type2;
		}
    MB_API
    static std::shared_ptr<mb::Node> create( const std::string& name,
      const std::string& tag = "Untagged" )
    {
      return std::make_shared<mb::Node>( name, tag );
    }
		MB_API
		// Creates GameObject from prefab and adds it to the scene.
		static Node* createFromPrefab( const Node& /*prefab*/ )
		{
			// TODO
			/**
			* Clone all components
			* Initialize all components
			*/
			return nullptr;
		}
		MB_API
		Node( Node&& other );
		MB_API
		Node& operator=( Node&& other );

		MB_API
		mb::NodePtr findByName( const std::string& name );
		MB_API
		mb::NodePtr findByTag( const std::string& tag );
		MB_API
		mb::NodePtr findById( const std::string uuid );

		MB_API
		Node( const std::string& name, const std::string& tag = "Untagged" );
		MB_API
		virtual ~Node( void );
		MB_API
		bool isVisible( void ) const;
		MB_API
		bool hasParent( void ) const;
		MB_API
		mb::NodePtr parent( void ) const;
		MB_API
		void setParent( mb::NodePtr p );
		MB_API
		void addChild( mb::NodePtr child );
		MB_API
		void removeChild( mb::NodePtr child );
		MB_API
		void removeChild( unsigned int index );
		MB_API
		unsigned int getNumChildren( void ) const;
		MB_API
		unsigned int getNumComponents( void ) const;
		MB_API
		mb::NodePtr getChild( unsigned int index );
		MB_API
		void removeChildren( void );
		MB_API
		void removeComponents( void );
		MB_API
		void addComponents( std::initializer_list<mb::ComponentPtr> components );
		MB_API
		void addComponent( const mb::ComponentPtr& c );
		MB_API
		void setVisible( const bool flag, const bool applyToChildren = false );
		MB_API
		std::vector<mb::NodePtr> children( void ) const;
		MB_API
		Transform& transform( void );
		MB_API
		void _updateMatrixWorld( bool force = false );
		MB_API
		std::string name( void ) const;
		MB_API
		std::string tag( void ) const;
		MB_API
		void name( const std::string& n );
		MB_API
		void tag( const std::string& t );
		MB_API
		std::vector<mb::ComponentPtr> getComponents( void ) const;
		MB_API
		MeshRenderer* getMesh(); // const;
		MB_API
		void traverse( const std::function<void( mb::NodePtr n )>& f );
		MB_API
		void traverseAncestors( const std::function<void( mb::NodePtr n )>& f );

		template <typename T>
		void toggleComponent( void );
		template <typename T>
		void enableComponent( void );
		template <class T>
		void disableComponent( void );
		template <class T>
		bool hasComponent(void) const;
		template <class T>
		T* getComponent(void);
		template <class T>
		void removeComponent(void);
		MB_API
		void removeComponent(mb::Component* c)
		{
			auto comp = std::begin(_components);
			while (comp != std::end(_components))
			{
				if (typeid(*comp->get()) == typeid(*c))
				{
					(*comp)->onDetach();
					_components.erase(comp);
					break;
				}
				++comp;
			}
		}

		template <typename T>
		T* componentInParent( void );
		/*template <typename T>
		std::vector<T*> componentsInParent( void );
		template <typename T>
		T* componentInChildren( void );
		template <typename T>
		std::vector<T*> componentsInChildren( void );*/

		MB_API
		mb::ComponentPtr getComponentByName( const std::string& name )
		{
			// TODO
			return nullptr;
		}

		MB_API
		mb::ComponentPtr getComponentByIndex( unsigned int index );
		MB_API
		friend std::ostream& operator<<( std::ostream & str, const Node& n );
		MB_API
		std::string uuid( void ) const;
		MB_API
		Layer& layer( void );
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

		// TODO: HARDCODED
		//std::vector<std::shared_ptr<Component>> mComponents;
		// TODO: HARDCODED

	private:
		mb::NodePtr _searchName( const std::string& name, const mb::NodePtr& elem );
		mb::NodePtr _searchTag( const std::string& tag, const mb::NodePtr& elem );
		mb::NodePtr _searchUUID( const std::string& uuid, const mb::NodePtr& elem );
	};
}

#include "Node.inl"

#endif /* __MB_NODE__ */

//template <typename T, bool = std::is_base_of<BaseComponent, T>::value>
