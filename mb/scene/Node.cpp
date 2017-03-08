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

#include "Node.hpp"
#include "components/MeshRendererTesselation.hpp"

namespace mb
{
  Node::Node( Node&& other )
  : _children( std::move( other._children ) )
  , _components( std::move( other._components ) )
  , _name( std::move( other._name ) )
  , _id( std::move( other._id ) )
  , _parent( std::move( other._parent ) )
  , _tag( std::move( other._tag ) )
  , _visible( std::move( other._visible ) )
  , _transform( std::move( other._transform ) )
  , _layer(std::move(other._layer ) )
  {
  }
  Node& Node::operator=( Node&& other )
  {
    if ( this != &other )
    {
      _children = std::move( other._children );
      _components = std::move( other._components );
      _name = std::move( other._name );
      _id = std::move( other._id );
      _parent = std::move( other._parent );
      _tag = std::move( other._tag );
      _visible = std::move( other._visible );
      _transform = std::move( other._transform );
      _layer = std::move( other._layer );
    }
    return *this;
  }
  /*void Node::setMesh(MeshRenderer* mesh)
  {
  mesh->setNode(this);
  this->_mesh = mesh;
  }*/
  // TODO: IMPROVE ...
  MeshRenderer* Node::getMesh( void ) /*const*/
  {
    auto comp = getComponent<MeshRenderer>( );
    if ( comp == nullptr )
    {
      comp = getComponent<MeshRendererTesselation>( );
    }
    return comp;
  }
  Node::Node( const std::string& name, const std::string& tag )
    : _name( name )
    , _id( mb::utils::generateUUID( ) )
    , _parent( nullptr )
    , _tag( tag )
    , _visible( true )
    , _transform( Transform( ) )
  {
    std::cout << "Node " << _name << " created" << std::endl;
  }
  Node::~Node( void )
  {
    std::cout << "REMOVE NODE " << name( ) << std::endl;
    removeChildren( );
    //removeComponents();
  }
  bool Node::isVisible( void ) const
  {
    return this->_visible;
  }
  bool Node::hasParent( void ) const
  {
    return this->_parent != nullptr;
  }
  mb::NodePtr Node::parent( void ) const
  {
    return this->_parent;
  }
  void Node::setParent( mb::NodePtr p )
  {
    // TODO: Check parent in p node (addChild or removeChild in p.parent)
    this->_parent = p;
  }
  mb::NodePtr Node::findByName( const std::string& name )
  {
    mb::NodePtr toRet = this->_searchName( name, mb::NodePtr( this ) );
    return toRet;
  }
  mb::NodePtr Node::findByTag( const std::string& tag )
  {
    mb::NodePtr toRet = this->_searchTag( tag, mb::NodePtr( this ) );
    return toRet;
  }
  mb::NodePtr Node::findById( const std::string uuid )
  {
    mb::NodePtr toRet = this->_searchUUID( uuid, mb::NodePtr( this ) );
    return toRet;
  }
  mb::NodePtr Node::_searchName( const std::string& name, const mb::NodePtr& elem )
  {
    if ( elem->hasParent( ) && elem->name( ) == name ) {
      return elem;
    }
    // Search in childrens
    for ( auto& c : elem->children( ) )
    {
      auto child = this->_searchName( name, c );
      if ( child )
      {
        return child;
      }
    }
    return nullptr;
  }
  mb::NodePtr Node::_searchTag( const std::string& tag, const mb::NodePtr& elem )
  {
    if ( elem->hasParent( ) && elem->tag( ) == tag )
    {
      return elem;
    }
    // Search in childrens
    for ( auto& c : elem->children( ) )
    {
      auto child = this->_searchTag( tag, c );
      if ( child )
      {
        return child;
      }
    }
    return nullptr;
  }
  mb::NodePtr Node::_searchUUID( const std::string& uuid, const mb::NodePtr& elem )
  {
    if ( elem->hasParent( ) && elem->uuid( ) == uuid ) {
      return elem;
    }
    // Search in childrens
    for ( auto& c : elem->children( ) )
    {
      auto child = this->_searchUUID( uuid, c );
      if ( child )
      {
        return child;
      }
    }
    return nullptr;
  }
  void Node::addChild( mb::NodePtr child )
  {
    if ( child.get( ) == this )
    {
      throw "TODO: ERROR";
    }
    for ( ComponentPtr comp : child->_components )
    {
      comp->start( );
    }
    if ( std::find( _children.begin( ), _children.end( ), child ) == _children.end( ) )
    {
      child->setParent( shared_from_this( ) );
      this->_children.push_back( child );
    }
  }
  void Node::removeChild( mb::NodePtr child )
  {
    auto it = std::find( _children.begin( ), _children.end( ), child );
    if ( it != _children.end( ) )
    {
      _children.erase( it );
    }
    child->_parent = nullptr;
  }
  void Node::removeChild( unsigned int index )
  {
    _children.erase( _children.begin( ) + index );
  }
  unsigned int Node::getNumChildren( void ) const
  {
    return _children.size( );
  }
  unsigned int Node::getNumComponents( void ) const
  {
    return _components.size( );
  }
  mb::NodePtr Node::getChild( unsigned int index )
  {
    if ( index >= _children.size( ) )
    {
      throw "Children dont found";
    }
    return _children.at( index );
  }
  void Node::removeChildren( void )
  {
    //std::for_each(_children.begin(), _children.end(), mb::utils::deleter<NodePtr>());
    _children.clear( );
  }
  void Node::removeComponents( void )
  {
    //std::for_each(_components.begin(), _components.end(),
    //	mb::utils::deleter<mb::ComponentPtr>());
	for (auto comp : _components)
	{
		comp->onDetach();
	}
	_components.clear( );
  }
  void Node::addComponents( std::initializer_list<mb::ComponentPtr> components )
  {
    for ( auto& comp : components )
    {
      addComponent( comp );
    }
  }
  void Node::addComponent( const mb::ComponentPtr& c )
  {
    // TODO: http://gamedev.stackexchange.com/questions/55950/entity-component-systems-with-c-accessing-components
    //this->_components[&typeid(*c)] = c;
    if ( std::find( _components.begin( ), _components.end( ), c ) == _components.end( ) )
    {
      c->setNode( this );
	  c->onAttach();
      if ( this->hasParent( ) )
      {
        c->start( );
      }
      this->_components.push_back( c );
    }
  }
  void Node::setVisible( const bool flag, const bool applyToChildren )
  {
    this->_visible = flag;
    if ( applyToChildren )
    {
      for ( auto& c : this->_children )
      {
        c->setVisible( flag, applyToChildren );
      }
    }
  }
  std::vector<mb::NodePtr> Node::children( void ) const
  {
    return this->_children;
  }
  Transform& Node::transform( void )
  {
    return this->_transform;
  }
  void Node::_updateMatrixWorld( bool force )
  {
    if ( this->_transform._autoUpdate )
    {
      this->_transform.updateMatrix( );
    }
    if ( this->_transform._matrixWorldNeedUpdate || force )
    {
      if ( !hasParent( ) )
      {
        this->transform( )._matrixWorld = this->transform( ).matrix( );
      }
      else
      {
        this->transform( )._matrixWorld = Mat4::mult2(
          this->_parent->transform( ).matrixWorld( ), this->transform( ).matrix( ) );
      }

      this->_transform._matrixWorldNeedUpdate = false;
      force = true;
    }

    for ( auto& child : _children )
    {
      child->_updateMatrixWorld( force );
    }
  }
  std::string Node::name( void ) const
  {
    return this->_name;
  }
  void Node::name( const std::string& n )
  {
    _name = n;
  }
  std::string Node::tag( void ) const
  {
    return this->_tag;
  }
  void Node::tag( const std::string& t )
  {
    this->_tag = t;
  }
  std::vector<mb::ComponentPtr> Node::getComponents( void ) const
  {
    return _components;
  }
  void Node::traverse( const std::function<void( mb::NodePtr n )>& f )
  {
    f( shared_from_this( ) );
    for ( auto& child : _children )
    {
      child->traverse( f );
    }
  }
  void Node::traverseAncestors( const std::function<void( mb::NodePtr n )>& f )
  {
    if ( this->_parent != nullptr )
    {
      f( shared_from_this( ) );
      this->_parent->traverseAncestors( f );
    }
  }
  mb::ComponentPtr Node::getComponentByIndex( unsigned int index )
  {
    if ( index >= _components.size( ) )
    {
      throw "Component dont found";
    }
    return _components.at( index );
  }
  std::ostream& operator<<( std::ostream & str, const Node& n )
  {
    str << n._name << " => " << n._id;
    return str;
  }
  std::string Node::uuid( void ) const
  {
    return _id;
  }
  Layer& Node::layer( void )
  {
    return _layer;
  }
}
