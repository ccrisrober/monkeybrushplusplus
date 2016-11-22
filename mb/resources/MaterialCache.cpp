/*
* Copyright (c) 2016 maldicion069
*
* Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
*
* This file is part of MonkeyBrushPlusPlus <https://github.com/maldicion069/monkeybrushplusplus>
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

#include "MaterialCache.hpp"

namespace MB
{
	std::unordered_map<std::string, Material*> MaterialCache::_files;
	void MaterialCache::add(const std::string& key, Material* value)
	{
		MaterialCache::_files[key] = value;
	}
	Material* MaterialCache::get(const std::string& key)
	{
		return MaterialCache::_files[key];
	}
	bool MaterialCache::exist(const std::string& key)
	{
		return MaterialCache::_files.find(key) == MaterialCache::_files.end();
	}
	void MaterialCache::remove(const std::string& key)
	{
		MaterialCache::_files.erase(key);
	}
	void MaterialCache::clear()
	{
		MaterialCache::_files.clear();
	}
}
