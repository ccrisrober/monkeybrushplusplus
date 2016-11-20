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

#ifndef __MB_SHADER_MATERIAL__
#define __MB_SHADER_MATERIAL__

#include "Material.hpp"

namespace MB
{
	typedef enum
	{
		VertexShader, FragmentShader, GeometryShader, TesselationEvaluationShader, TesselationControlShader
	} ShaderType;
	class ShaderMaterial: public Material
	{
	public:
		ShaderMaterial(
			const std::vector<std::pair<ShaderType, const char*> >& shaders,
			const std::vector<std::pair<const char*, Uniform*> >& uniforms)
		: Material()
		{
			for (const auto& pair : uniforms)
			{
				_uniforms[pair.first] = pair.second;
			}
			for (const auto& pair : shaders)
			{
				switch (pair.first)
				{
				case VertexShader:
					_program.loadVertexShaderFromText(pair.second);
					break;
				case FragmentShader:
					_program.loadFragmentShaderFromText(pair.second);
					break;
				case GeometryShader:
					_program.loadGeometryShaderFromText(pair.second);
					break;
				case TesselationEvaluationShader:
					_program.loadTesselationEvaluationShaderFromText(pair.second);
					break;
				case TesselationControlShader:
					_program.loadTesselationControlShaderFromText(pair.second);
					break;
				}
			}
			_program.compileAndLink();
			_program.autocatching();
		}
	};
}

#endif /* __MB_SHADER_MATERIAL__ */