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

#include <mb/api.h>

#include <unordered_map>
#include "Uniform.hpp"
#include "../core/Program.hpp"
#include "../maths/Vect2.hpp"
#include "../maths/Vect3.hpp"
#include "../maths/Vect4.hpp"
#include "../maths/Mat2.hpp"
#include "../maths/Mat3.hpp"
#include "../maths/Mat4.hpp"

namespace MB
{
    typedef std::unordered_map<std::string, Uniform*> TUniforms;
	class Material
	{
	public:
		MB_API
		Material();
		MB_API
        virtual ~Material();
		MB_API
        TUniforms& uniforms();
		MB_API
        Uniform*& uniform(const std::string& name);
		MB_API
		virtual void use();
		MB_API
		virtual void unuse();
		MB_API
		std::string id;
		MB_API
		bool backFaceCull = true;
		MB_API
		unsigned int sizeOrientation; // InvClockWise
		MB_API
		bool depthTest = true;
		MB_API
		bool visible = true;
	protected:
		TUniforms _uniforms;
        Program _program;
	};
}

#endif /* __MB_MATERIAL__ */
