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

#ifndef __MB_RESOURCE_SHADER__
#define __MB_RESOURCE_SHADER__

#include <unordered_map>
#include <fstream>
#include <sstream>

namespace MB
{
	class ResourceShader
	{
	public:
		static void add(const char* key, const char* value)
		{
			_files[key] = value;
		}
		static const char* get(const char* key)
		{
			return _files[key];
		}
		static bool exist(const char* key)
		{
			return _files.find(key) == _files.end();
		}
		static void remove(const char* key)
		{
			_files.erase(key);
		}
		static void clear()
		{
			_files.clear();
		}
		static void loadShader(const char* alias, const char* filePath)
		{
			std::ifstream file(filePath);
			std::stringstream buffer;
			buffer << file.rdbuf();
			const char* src = buffer.str().c_str();
			ResourceShader::loadShaderFromText(alias, src);
		}
		static void loadShaderFromText(const char* alias, const char* shaderSource)
		{
			ResourceShader::add(alias, shaderSource);
		}
	protected:
		static std::unordered_map<const char*, const char*> _files;
	};
	std::unordered_map<const char*, const char*> ResourceShader::_files;
}

#endif /* __MB_RESOURCE_SHADER__ */
