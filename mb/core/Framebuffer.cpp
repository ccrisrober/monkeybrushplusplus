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

#include "Framebuffer.hpp"

namespace MB
{
	Framebuffer::Framebuffer(const std::vector<Texture*>& textures, 
		const Vect2& size, bool depth)
	: _valid(false)
	, _size(size)
	{
		glCreateFramebuffers(1, &_handler);
		unsigned int numColors = 0;
		if (numColors < 1) {
			throw ("must specify >= 0 color attachments");
		}
		else if (numColors > 1) {
			//if (numColors > gl.getParameter(MB.ctes.DrawBuffer.MaxColorAttch)) {
			//	throw (`GL context doesn´t support ${ numColors } color attachments`);
			//}
		}
		this->_attachments = textures;
		unsigned int target, i = 0;
		for (auto& tex : this->_attachments)
		{
			tex->bind();
			target = tex->target();

			glFramebufferTexture2D(GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0 + i,
				target,
				tex->handler(), 0);
			++i;
		}
		this->_attachments.back()->unbind();
		if (depth)
		{
			this->_renderBuffer = new RenderBufferTexture(size,
				GL_DEPTH_COMPONENT16,
				GL_DEPTH_ATTACHMENT);
		}

		if (numColors > 1)
		{
			std::vector<GLenum> drawBuffs(numColors);
			for (unsigned int ii = 0; ii < numColors; ++ii)
			{
				drawBuffs[ii] = GL_COLOR_ATTACHMENT0 + ii;
			}
			glDrawBuffers(numColors, &drawBuffs[0]);
		}

		// Check status
		auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			// TODO: Destroy
			this->checkStatus(status);
		}
		this->_valid = true;
		this->unbind();
	}
	Framebuffer::~Framebuffer()
	{
		/*let oldBinding = gl.getParameter(gl.FRAMEBUFFER_BINDING);

		if (oldBinding == this->_handler) {
			gl.bindFramebuffer(gl.FRAMEBUFFER, 0);
		}*/

		// TODO: Destroy attachments
		if (_renderBuffer)
		{
			delete(_renderBuffer);
			_renderBuffer = nullptr;
		}
		glDeleteFramebuffers(1, &_handler);
	}
	void Framebuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _handler);
	}
	void Framebuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void Framebuffer::replaceTexture(Texture* tex, unsigned attach)
	{
		if (attach > this->_attachments.size())
		{
			throw ("Attachment undefined");
		}
		this->_attachments[attach] = tex;
		glFramebufferTexture2D(GL_FRAMEBUFFER, 
			GL_COLOR_ATTACHMENT0 + attach,
			GL_TEXTURE_2D, tex->handler(), 0);
	}
	void Framebuffer::rebuild(Vect2& size)
	{
		if (size != _size)
		{
			for (auto& tex : _attachments)
			{
				tex->resize(size);
			}
			if (_renderBuffer)
			{
				_renderBuffer->resize(size);
			}
		}
	}
	void Framebuffer::onlyBindTextures()
	{
		this->unbind();
		unsigned int idx = 0;
		for (auto& tex : _attachments)
		{
			tex->bind(idx);
			++idx;
		}
	}
	void Framebuffer::RestoreDefaultFBO()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	bool Framebuffer::isValid()
	{
		this->bind();
		this->_valid = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		this->unbind();

		return _valid;
	}
	void Framebuffer::checkStatus(unsigned int status)
	{
		switch (status) {
		case GL_FRAMEBUFFER_UNSUPPORTED:
			throw ("Framebuffer: Framebuffer unsupported");
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			throw ("Framebuffer: Framebuffer incomplete attachment");
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
			throw ("Framebuffer: Framebuffer incomplete dimensions");
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			throw ("Framebuffer: Framebuffer incomplete missing attachment");
		default:
			throw ("Framebuffer: Framebuffer failed for unspecified reason");
		}
	}
}
