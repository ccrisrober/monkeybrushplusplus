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

#include "Component.hpp"

namespace mb
{
  Component::Component( void )
  {

  }
#ifdef MB_USE_RAPIDJSON
  Component::Component(const Value& /*config*/)
  {

  }
#endif
  Component::~Component( void )
  {
    std::cout << "REMOVE COMPONENT " << std::endl;
  }
  void Component::start( void )
  {
  }
  void Component::fixedUpdate( const float& )
  {
  }
  void Component::update( const mb::Clock& )
  {
  }
  Node* Component::getNode( void ) const
  {
    return this->_node;
  }
  void Component::setNode(Node* n)
  {
    this->_node = n;
  }
  std::ostream& operator<<(std::ostream & str, const Component& n)
  {
    str << typeid(n).name();
    return str;
  }
  bool Component::isEnabled() const
  {
    return _enabled;
  }
  void Component::enable( void )
  {
    setEnabled(true);
  }
  void Component::disable( void )
  {
    setEnabled(false);
  }
  void Component::setEnabled(const bool v)
  {
    _enabled = v;
  }
  void Component::toggle( void )
  {
    setEnabled(!isEnabled( ));
  }
  void Component::onAttach( void )
  {
	  std::cout << "Attach component" << std::endl;
  }
  void Component::onDetach( void )
  {
	  std::cout << "Dettach component" << std::endl;
  }
}
