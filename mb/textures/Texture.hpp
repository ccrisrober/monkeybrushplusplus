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

#ifndef __MB_TEXTURE__
#define __MB_TEXTURE__

#include <mb/api.h>

#include "../Includes.hpp"

#include "../maths/Vect2.hpp"

#include <iostream>
#include <functional>

#include "../constants/Constants.hpp"

namespace mb
{
  struct TexOptions
  {
    unsigned int internalFormat = GL_RGBA;
    unsigned int format = GL_RGBA;
    unsigned int border = 0;
    mb::ctes::TextureFilter minFilter = mb::ctes::TextureFilter::Linear;
    mb::ctes::TextureFilter magFilter = mb::ctes::TextureFilter::Linear;
    unsigned int type = GL_UNSIGNED_BYTE;
    unsigned int level = 0;
    mb::ctes::WrapMode wrapS = mb::ctes::WrapMode::Clamp2Edge;
    mb::ctes::WrapMode wrapT = mb::ctes::WrapMode::Clamp2Edge;
    mb::ctes::WrapMode wrapR = mb::ctes::WrapMode::Clamp2Edge;
    unsigned int packAlignment = 0;
    unsigned int unpackAlignment = 0;
    bool autoMipmap = false;
  };
  class Texture
  {
  public:
    MB_API
    virtual ~Texture( ) = 0;
    MB_API
    void bind( int slot = -1 );
    MB_API
    void unbind( );
    MB_API
    unsigned int handler( ) const;
    MB_API
    unsigned int target( ) const;
    MB_API
    bool isLoaded( ) const;
    MB_API
    virtual void resize(const Vect2& /*size*/) {
  }
  protected:
    Texture( const TexOptions& options, unsigned int type );

    virtual void load() { _loaded = true; }

    bool _loaded = false;
    unsigned int _target;
    unsigned int _handler;

    unsigned int _internalFormat;
    unsigned int _format;
    unsigned int _border;
    mb::ctes::TextureFilter _minFilter;
    mb::ctes::TextureFilter _magFilter;
    unsigned int _type;
    unsigned int _level;
    mb::ctes::WrapMode _wrapS;
    mb::ctes::WrapMode _wrapT;
    mb::ctes::WrapMode _wrapR;
    unsigned int _packAlignment;
    unsigned int _unpackAlignment;
  };
}

#endif /* __MB_TEXTURE__ */
