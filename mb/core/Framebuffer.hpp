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

#ifndef __MB_FRAMEBUFFER__
#define __MB_FRAMEBUFFER__

#include <mb/api.h>

#include <vector>
#include "../textures/Texture.hpp"
#include "../textures/RenderBuffer.hpp"
#include "../textures/RenderBufferTexture.hpp"
#include "../maths/Vect2.hpp"

namespace MB
{
	class Framebuffer
	{
	public:
		MB_API
		Framebuffer(const std::vector<Texture*>& textures, 
			const Vect2& size, bool depth = true);
		MB_API
		virtual ~Framebuffer();
		MB_API
		void bind();
		MB_API
		void unbind();
		MB_API
		void replaceTexture(Texture* tex, unsigned attach);
		MB_API
		void rebuild(Vect2& size);
		MB_API
		void onlyBindTextures();
		MB_API
		static void RestoreDefaultFBO();
		MB_API
		bool isValid();
	protected:
		bool _valid;
		Vect2 _size;
		unsigned int _handler;
		std::vector<Texture*> _attachments;
		RenderBuffer* _renderBuffer;

	private:
		void checkStatus(unsigned int status);
	};
}

#endif /* __MB_FRAMEBUFFER__ */
