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

#ifndef __MB_RESOURCE_SHADER__
#define __MB_RESOURCE_SHADER__

#include <mb/api.h>

#include <unordered_map>
#include <fstream>
#include <sstream>

namespace mb
{
  class ResourceShader
  {
  public:
    static const std::string& get(const std::string& key);
    static bool exist(const std::string& key);
  public:
    MB_API
    static void loadShader(const std::string& alias, const std::string& filePath);
    MB_API
    static void loadShaderFromText(const std::string& alias, const std::string& shaderSource);
  protected:
    static void add(const std::string& key, const std::string& value);
    static void remove(const std::string& key);
    static void clear();

    static std::unordered_map<std::string, std::string> _files;
  };
}

#endif /* __MB_RESOURCE_SHADER__ */
