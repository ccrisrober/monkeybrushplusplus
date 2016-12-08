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

#include "Texture2D.hpp"
#include <FreeImage.h>

namespace mb
{
  Texture2D::Texture2D(const TexOptions& options,
    unsigned int width, unsigned int height)
    : Texture2D(options, nullptr, width, height)
  {
  }
  Texture2D::Texture2D(const TexOptions& options, void* data,
    unsigned int width, unsigned int height)
    : Texture(options, GL_TEXTURE_2D)
    , _width(width)
    , _height(height)
  {
    glGenTextures(1, &this->_handler);

    glBindTexture( this->_target, this->_handler );

    this->configTexture( data );
    this->_loaded = true;
  }
  Texture2D::Texture2D(const TexOptions& options, const std::string src)
    : Texture(options, GL_TEXTURE_2D)
    , _src(src)
  {
  }
  Texture2D::~Texture2D(void)
  {
  }
  void Texture2D::configTexture( void* data )
  {
    glTexImage2D(
      this->_target,
      this->_level,
      this->_internalFormat,
      this->_width,
      this->_height,
      this->_border,
      this->_format,
      this->_type,
      data
    );

    glTexParameteri( this->_target, GL_TEXTURE_MIN_FILTER,
      static_cast<int>(this->_minFilter ));
    glTexParameteri( this->_target, GL_TEXTURE_MAG_FILTER,
      static_cast<int>(this->_magFilter ));
    glTexParameteri(this->_target, GL_TEXTURE_WRAP_S,
      static_cast<int>(this->_wrapS));
    glTexParameteri(this->_target, GL_TEXTURE_WRAP_T,
      static_cast<int>(this->_wrapT));

    this->unbind( );
  }
  void Texture2D::load( void )
  {
    if ( !this->_loaded )
    {
      glGenTextures( 1, &this->_handler );

      glBindTexture( this->_target, this->_handler );

      auto pixels = this->loadTexture( this->_src.c_str( ), this->_width, this->_height );

      this->configTexture( pixels );
      this->_loaded = true;
    }
  }
  unsigned char* Texture2D::loadTexture( const char* fileName_,
    unsigned int& width_,
    unsigned int& height_ )
  {
    FreeImage_Initialise( TRUE );

    FREE_IMAGE_FORMAT format = FreeImage_GetFileType( fileName_, 0 );
    if ( format == FIF_UNKNOWN )
    {
      format = FreeImage_GetFIFFromFilename( fileName_ );
    }
    if ( ( format == FIF_UNKNOWN ) || !FreeImage_FIFSupportsReading( format ) )
    {
      return nullptr;
    }

    FIBITMAP* img = FreeImage_Load( format, fileName_ );
    if ( img == nullptr )
    {
      return nullptr;
    }

    FIBITMAP* tempImg = img;
    img = FreeImage_ConvertTo32Bits( img );
    FreeImage_Unload( tempImg );

    width_ = FreeImage_GetWidth( img );
    height_ = FreeImage_GetHeight( img );

    //BGRA a RGBA
    unsigned char * map = new unsigned char[ 4 * width_*height_ ];
    char *buff = ( char* )FreeImage_GetBits( img );

    for ( unsigned int j = 0; j < width_*height_; ++j )
    {
      map[ j * 4 + 0 ] = buff[ j * 4 + 2 ];
      map[ j * 4 + 1 ] = buff[ j * 4 + 1 ];
      map[ j * 4 + 2 ] = buff[ j * 4 + 0 ];
      map[ j * 4 + 3 ] = buff[ j * 4 + 3 ];
    }

    FreeImage_Unload( img );
    FreeImage_DeInitialise( );

    return map;
  }
  void Texture2D::resize(int w, int h)
  {
    resize(w, h, nullptr);
  }
  void Texture2D::resize(int w, int h, void* data)
  {
    _width = w;
    _height = h;
    this->bind();
    configTexture(data);
  }
  void Texture2D::bindImageTexture(unsigned int unit, unsigned int level,
    unsigned int layered, unsigned int layer, unsigned int access,
    unsigned int format)
  {
    glBindImageTexture(unit, _handler, level, layered, layer, access, format);
  }
  unsigned int Texture2D::getWidth() const
  {
    return _width;
  }
  unsigned int Texture2D::getHeight() const
  {
    return _height;
  }
  std::string Texture2D::src() const
  {
    return _src;
  }
}

