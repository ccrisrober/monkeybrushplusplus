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

#ifndef __MB_MATERIAL__
#define __MB_MATERIAL__

#include <unordered_map>
#include "Uniform.hpp"
#include "../core/Program.hpp"
#include "../maths/Vect3.hpp"
#include "../maths/Mat4.hpp"

namespace MB
{
    typedef std::unordered_map<std::string, Uniform*> TUniforms;
	class Material
	{
	public:
		Material()
		{
		}
		TUniforms& uniforms() {
			return this->_uniforms;
		}
		virtual void use()
		{
			this->_program.use();
			for (const auto& uniform : _uniforms)
			{
				if (!uniform.second->isDirty())
					continue;
				switch (uniform.second->type())
				{
					case Vector3:
					{
						auto value = uniform.second->value();
						this->_program.sendUniform3v(uniform.first, &uniform.second->value().cast<Vect3>()._values[0]);
						break;
					}
					case Matrix4:
					{
						auto value = uniform.second->value();
						this->_program.sendUniform4m(uniform.first, &uniform.second->value().cast<Mat4>()._values[0]);
						break;
					}
				}
				uniform.second->setDirty(false);
			}
			//this->_program.unuse();
		}
		std::string id;
		bool backFaceCull = true;
		unsigned int sizeOrientation; // InvClockWise
		bool depthTest = true;
		bool visible = true;
	protected:
		TUniforms _uniforms;
        Program _program;
	};
}

#endif /* __MB_MATERIAL__ */
