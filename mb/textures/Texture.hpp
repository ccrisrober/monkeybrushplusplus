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

#ifndef __MB_TEXTURE__
#define __MB_TEXTURE__

#include <mb/api.h>

#include "../Includes.hpp"

#include "../maths/Vect2.hpp"

#include <iostream>
#include <functional>

namespace MB
{
    struct TexOptions
    {
        unsigned int internalFormat = GL_RGBA;
        unsigned int format = GL_RGBA;
        unsigned int border = 0;
        unsigned int minFilter = GL_LINEAR;
        unsigned int magFilter = GL_LINEAR;
        unsigned int type = GL_UNSIGNED_BYTE;
        unsigned int level = 0;
        unsigned int wrapS = GL_CLAMP_TO_EDGE;
        unsigned int wrapT = GL_CLAMP_TO_EDGE;
        unsigned int wrapR = GL_CLAMP_TO_EDGE;
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
        inline unsigned int handler( ) const
        {
            return this->_handler;
        }
        MB_API
        inline unsigned int target( ) const
        {
            return this->_target;
        }
        MB_API
        inline bool isLoaded( ) const
        {
            return this->_loaded;
        }
        MB_API
		virtual void resize(const Vect2& /*size*/) {

		}
    protected:
        Texture( const TexOptions& options, unsigned int type );

		virtual void load() { _loaded = true; }//= 0;

        bool _loaded = false;
        unsigned int _target;
        unsigned int _handler;

        unsigned int _internalFormat;
        unsigned int _format;
        unsigned int _border;
        unsigned int _minFilter;
        unsigned int _magFilter;
        unsigned int _type;
        unsigned int _level;
        unsigned int _wrapS;
        unsigned int _wrapT;
        unsigned int _wrapR;
    };
}

#endif /* __MB_TEXTURE__ */
