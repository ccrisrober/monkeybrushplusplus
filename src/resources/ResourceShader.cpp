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

#include "ResourceShader.hpp"

namespace MB
{
	std::unordered_map<std::string, std::string> ResourceShader::_files;
	
	void ResourceShader::add(const std::string& key, const std::string& value)
	{
		_files[key] = value;
	}
	const std::string& ResourceShader::get(const std::string& key)
	{
		return _files[key];
	}
	bool ResourceShader::exist(const std::string& key)
	{
		return _files.find(key) == _files.end();
	}
	void ResourceShader::remove(const std::string& key)
	{
		_files.erase(key);
	}
	void ResourceShader::clear()
	{
		_files.clear();
	}
	void ResourceShader::loadShader(const std::string& alias, const std::string& filePath)
	{
		std::ifstream file(filePath);
		std::stringstream buffer;
		buffer << file.rdbuf();
		const std::string& src = buffer.str();
		ResourceShader::loadShaderFromText(alias, src);
	}
	void ResourceShader::loadShaderFromText(const std::string& alias, const std::string& shaderSource)
	{
		ResourceShader::add(alias, shaderSource);
	}
}
