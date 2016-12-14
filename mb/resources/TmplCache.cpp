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

#include "TmplCache.hpp"

namespace mb
{
  std::unordered_map<std::string, T> TmplCache::_files;
  void TmplCache::add(const std::string& key, T value)
  {
    TmplCache::_files[key] = value;
  }
  T TmplCache::get(const std::string& key)
  {
    return TmplCache::_files[key];
  }
  bool TmplCache::exist(const std::string& key)
  {
    return TmplCache::_files.find(key) == TmplCache::_files.end();
  }
  void TmplCache::remove(const std::string& key)
  {
    TmplCache::_files.erase(key);
  }
  void TmplCache::clear()
  {
    TmplCache::_files.clear();
  }
}
