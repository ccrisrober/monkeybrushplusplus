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

#ifndef __MB_RENDERBUFFER_MULTISAMPLE_TEXTURE__
#define __MB_RENDERBUFFER_MULTISAMPLE_TEXTURE__

#include "RenderBuffer.hpp"

namespace MB
{
	class RenderBufferMultisampleTexture: public RenderBuffer
	{
	public:
		RenderBufferMultisampleTexture(const Vect2& size, unsigned int format, unsigned int attachment)
			: RenderBuffer(size, format, attachment)
		{
			this->bind();
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, _format, (unsigned int)_size.x(), (unsigned int)size.y());
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, _attachment, GL_RENDERBUFFER, _handler);
			this->unbind();
		}
		virtual void resize(const Vect2& size)
		{
			this->bind();
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, _format, (unsigned int)_size.x(), (unsigned int)size.y());
			this->unbind();
		}
	};
}

#endif /* __MB_RENDERBUFFER_MULTISAMPLE_TEXTURE__ */