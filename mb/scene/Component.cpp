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
  void Component::start()
  {
  }
  void Component::update(float)
  {
  }
  Node* Component::getNode() const
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
  void Component::enable()
  {
    setEnabled(true);
  }
  void Component::disable()
  {
    setEnabled(false);
  }
  void Component::setEnabled(const bool v)
  {
    _enabled = v;
  }
  void Component::toggle()
  {
    setEnabled(!isEnabled());
  }
}
