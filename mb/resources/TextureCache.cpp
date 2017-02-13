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

#include "TextureCache.hpp"

namespace mb
{
  std::unordered_map<std::string, mb::TexturePtr> TextureCache::_files;
  void TextureCache::add(const std::string& key, mb::TexturePtr value)
  {
    TextureCache::_files[key] = value;
  }
  mb::TexturePtr TextureCache::get(const std::string& key)
  {
    return TextureCache::_files[key];
  }
  bool TextureCache::exist(const std::string& key)
  {
    return TextureCache::_files.find(key) == TextureCache::_files.end();
  }
  void TextureCache::remove(const std::string& key)
  {
    TextureCache::_files.erase(key);
  }
  void TextureCache::clear()
  {
    TextureCache::_files.clear();
  }
}
