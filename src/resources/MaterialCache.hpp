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

#ifndef __MB_MATERIAL_CACHE__
#define __MB_MATERIAL_CACHE__

#include <unordered_map>
#include "../materials/Material.hpp"

namespace MB
{
	class MaterialCache
	{
	public:
		static void add(const std::string& key, Material* value);
		static Material* get(const std::string& key);
		static bool exist(const std::string& key);
		static void remove(const std::string& key);
		static void clear();
	protected:
		static std::unordered_map<std::string, Material*> _files;
	};
}

#endif /* __MB_MATERIAL_CACHE__ */
