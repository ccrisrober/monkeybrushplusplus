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

#include "Texture.hpp"

namespace mb
{
  Texture::Texture( const TexOptions& options, unsigned int type )
  : _handler( -1 )
  {
    this->_target = type;
    this->_level = options.level;
    this->_border = options.border;
    this->_internalFormat = options.internalFormat;
    this->_format = options.format;
    this->_type = options.type;

    this->_wrapS = options.wrapS;
    this->_wrapT = options.wrapT;
    this->_wrapR = options.wrapR;

    this->_minFilter = options.minFilter;
    this->_magFilter = options.magFilter;

    this->_packAlignment = options.packAlignment;
    this->_unpackAlignment = options.unpackAlignment;
  }
  Texture::~Texture( )
  {
    glDeleteTextures( 1, &this->_handler );
    this->_handler = -1;
  }
  void Texture::bind( int slot )
  {
    this->load( );
    if ( slot >= 0 )
    {
      glActiveTexture( GL_TEXTURE0 + slot );
    }
    glBindTexture( this->_target, this->_handler );
  }
  void Texture::unbind( )
  {
    glBindTexture( this->_target, -1 );
  }
  unsigned int Texture::handler( ) const
  {
    return this->_handler;
  }
  MB_API
  unsigned int Texture::target( ) const
  {
    return this->_target;
  }
  MB_API
  bool Texture::isLoaded( ) const
  {
    return this->_loaded;
  }
}
