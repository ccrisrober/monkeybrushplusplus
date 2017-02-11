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

#include "NodeData.hpp"

namespace mb
{
  NodeData::NodeData( const std::string& name, const std::string& tag )
    : Node(name, tag)
  {

  }
  void NodeData::insertData( const std::string& name, const mb::any& data )
  {
    _userData[name] = data;
  }
  mb::any NodeData::getData( const std::string& name )
  {
    return _userData[name];
  }
  bool NodeData::removeData( const std::string& name )
  {
    auto it = _userData.find( name );
    if ( it != _userData.end( ) )
    {
      _userData.erase( name );
      return true;
    }
    return false;
  }
}
