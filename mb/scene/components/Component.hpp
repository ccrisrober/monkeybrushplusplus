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

#ifndef __MB_COMPONENT__
#define __MB_COMPONENT__

#include <mb/api.h>

#include <iostream>
#include <typeinfo>
#include <memory>
#include "../../maths/Clock.hpp"

#ifdef MB_USE_RAPIDJSON
  #include <rapidjson/document.h>
  using namespace rapidjson;
#endif

// TODO RTTI
//#include "../utils/RTTI.hpp"

namespace mb
{
  class Node;
  class Component//: public RTTI
  {
  //MB_IMPLEMENT_RTTI(mb::Component)
  public:
    //MB_API
    //virtual const char *getComponentName(void) const { return getClassName(); }
    MB_API
    virtual void start( void );
  	MB_API
  	virtual void fixedUpdate( const float& dt );
    MB_API
    virtual void update( const mb::Clock& clock );
    MB_API
    Node* getNode( void ) const;
    MB_API
    void setNode(Node* n);  // TODO: Trying to move to private
    MB_API
    friend std::ostream& operator<<( std::ostream & str, const Component& n );
    MB_API
    bool isEnabled( void ) const;
    MB_API
    void enable( void );
    MB_API
    void disable( void );
    MB_API
    void setEnabled( const bool v );
    MB_API
    void toggle( void );
    MB_API
    virtual ~Component( void );
  	MB_API
  	// Invoked once when component is attached to a node
  	virtual void onAttach( void );
  	MB_API
  	// Invoked once when component is detached from a node
  	virtual void onDetach( void );
  protected:
  #ifdef MB_USE_RAPIDJSON
    Component( const Value& /*config*/ );
  #endif
    Component( void );
    Node* _node;
    bool _enabled = true;
  };
  typedef std::shared_ptr<Component> ComponentPtr;
}

#endif /* __MB_COMPONENT__ */
