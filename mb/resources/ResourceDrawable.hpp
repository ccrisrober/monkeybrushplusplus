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

#ifndef __MB_RESOURCE_DRAWABLE__
#define __MB_RESOURCE_DRAWABLE__

#include <mb/api.h>

#include <unordered_map>
#include "../models/Drawable.hpp"

namespace mb
{
	class ResourceDrawable
	{
	public:
		MB_API
		static void add(const std::string& key, Drawable* value);
		MB_API
		static Drawable* get(const std::string& key);
		MB_API
		static bool exist(const std::string& key);
		MB_API
		static void remove(const std::string& key);
		MB_API
		static void clear();
	protected:
		static std::unordered_map<std::string, Drawable*> _files;
	};
}

#endif /* __MB_RESOURCE_DRAWABLE__ */
