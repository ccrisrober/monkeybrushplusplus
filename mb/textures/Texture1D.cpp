/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 * <https://github.com/maldicion069/monkeybrushplusplus>
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

#include "Texture1D.hpp"

namespace mb
{
	Texture1D::Texture1D( const TexOptions& options, void* data, unsigned int w )
	: Texture(options, GL_TEXTURE_1D)
	, _width( w )
	{
		glGenTextures(1, &this->_handler);

		glBindTexture( this->_target, this->_handler );

		this->configTexture( data );
		this->_loaded = true;
	}
	Texture1D::~Texture1D( void ) {
  }
	void Texture1D::load( void )
	{
  }
	void Texture1D::configTexture( void* data )
	{
		if (_packAlignment > 0)
		{
 	 		glPixelStorei(GL_PACK_ALIGNMENT, this->_packAlignment);
		}
		if (_unpackAlignment > 0)
		{
	  		glPixelStorei(GL_UNPACK_ALIGNMENT, this->_unpackAlignment);
		}

		glTexParameteri( this->_target, GL_TEXTURE_MIN_FILTER,
      static_cast<int>(this->_minFilter ));
		glTexParameteri( this->_target, GL_TEXTURE_MAG_FILTER,
      static_cast<int>(this->_magFilter ));
		glTexParameteri( this->_target, GL_TEXTURE_WRAP_S,
      static_cast<int>(this->_wrapS ));
		glTexParameteri( this->_target, GL_TEXTURE_WRAP_T,
      static_cast<int>(this->_wrapT ));

		glTexImage1D(
			this->_target,
			this->_level,
			this->_internalFormat,
			this->_width,
			this->_border,
			this->_format,
			this->_type,
		data
		);

		this->unbind( );
	}
}

