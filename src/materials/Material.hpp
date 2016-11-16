/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal
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

#ifndef __MB_MATERIAL__
#define __MB_MATERIAL__

#include <unordered_map>

namespace MB
{
	typedef enum
	{
		Float, Integer, Unsigned, Boolean, Vector2, Vector3, Vector4, Matrix2, Matrix3, Matrix4
	} UniformType;
	struct UniformMaterial {
		UniformMaterial(UniformType _type, void* _value)
		{
			this->type = _type;
			this->value = _value;
		}
		UniformType type;
		void* value;
	};
	typedef std::unordered_map<std::string, UniformMaterial> TUniforms;
	class Material
	{
	public:
		Material()
		{
		}
		TUniforms& uniforms() {
			return this->_uniforms;
		}
		void use()
		{

		}
		std::string id;
		bool backFaceCull = true;
		unsigned int sizeOrientation; // InvClockWise
		bool depthTest = true;
		bool visible = true;
	protected:
		TUniforms _uniforms;
	};
}

#endif /* __MB_MATERIAL__ */