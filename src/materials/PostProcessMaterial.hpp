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

#ifndef __MB_POST_PROCESS_MATERIAL__
#define __MB_POST_PROCESS_MATERIAL__

#include "Material.hpp"
#include "Uniform.hpp"
#include "../core/PostProcess.hpp"

namespace MB
{
	class PostProcessMaterial : public Material
	{
	public:
		PostProcessMaterial(const char* fsShader_ = nullptr)
			: Material()
		{
			const char* vsShader = 
				"#version 330\n"
				"layout(location = 0) in vec3 vertPosition\n;"
				"out vec2 uv;\n"
				"void main(void) {\n"
				"	uv = vec2(vertPosition.xy * 0.5) + vec2(0.5);\n"
				"	gl_Position = vec4(vertPosition, 1.0)\n;"
				"}\n";
			const char* fsShader;
			if (fsShader_)
			{
				fsShader = fsShader_;
			}
			else
			{
				fsShader = 
					"#version 330\n"
					"uniform vec3 color;\n"
					"out vec4 fragColor;\n"
					"in vec2 uv;\n"
					""
					"void main()\n"
					"{\n"
					"    fragColor = vec4(uv, 0.0, 1.0);\n"
					"}\n";
			}
			
			_program.loadFromText(vsShader, fsShader);
			_program.compileAndLink();
			_program.autocatching();

			_pp = new PostProcess();
		}
		void renderPP()
		{
			this->use();
			this->_pp->bind();
		}
	protected:
		/* TODO: static ?? */ PostProcess *_pp;
	};
}

#endif /* __MB_POST_PROCESS_MATERIAL__ */
