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

#ifndef __MB_TEXTURE2DARRAY__
#define __MB_TEXTURE2DARRAY__

#include "Texture.hpp"
#include <vector>

namespace MB
{
	class Texture2DArray : public Texture
	{
	public:
		Texture2DArray(const TexOptions& options, std::vector< void* > data,
			unsigned int width, unsigned int height)
			: Texture(options, GL_TEXTURE_2D_ARRAY)
		{
			this->load();
			glBindTexture(this->_target, this->_handler);
			glTexImage3D(this->_target, this->_level, this->_internalFormat,
				width, height, data.size(), 0, this->_format, this->_type, nullptr);

			unsigned int i = 0;
			for (const auto& layer : data)
			{
				glTexSubImage3D(
					this->_target, 0, 0, 0, i, width, height, 1,
					this->_format, this->_type, layer
				);
				++i;
			}
			glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER, this->_minFilter);
			glTexParameteri(this->_target, GL_TEXTURE_MAG_FILTER, this->_magFilter);
			glTexParameteri(this->_target, GL_TEXTURE_WRAP_S, this->_wrapS);
			glTexParameteri(this->_target, GL_TEXTURE_WRAP_T, this->_wrapT);
			glTexParameteri(this->_target, GL_TEXTURE_WRAP_R, this->_wrapR);
			this->unbind();
		}
		~Texture2DArray(void)
		{
		}
		void load(void)
		{
			if (!this->_loaded) {
				glGenTextures(1, &this->_handler);
				glBindTexture(this->_target, this->_handler);
				this->_loaded = true;
			}
		}
	};
}

#endif /* __MB_TEXTURE2DARRAY__ */