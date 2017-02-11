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

#include "ResourceDrawable.hpp"

namespace mb
{
  std::unordered_map<std::string, mb::DrawablePtr> ResourceDrawable::_files;
  void ResourceDrawable::add(const std::string& key, mb::DrawablePtr value)
  {
    ResourceDrawable::_files[key] = value;
  }
  mb::DrawablePtr ResourceDrawable::get(const std::string& key)
  {
    return ResourceDrawable::_files[key];
  }
  bool ResourceDrawable::exist(const std::string& key)
  {
    return ResourceDrawable::_files.find(key) == ResourceDrawable::_files.end();
  }
  void ResourceDrawable::remove(const std::string& key)
  {
    ResourceDrawable::_files.erase(key);
  }
  void ResourceDrawable::clear()
  {
    ResourceDrawable::_files.clear();
  }
}
