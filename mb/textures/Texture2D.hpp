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

#ifndef __MB_TEXTURE2D__
#define __MB_TEXTURE2D__

#include <mb/api.h>

#include "Texture.hpp"

namespace MB
{
	class Texture2D : public Texture
	{
	public:
		MB_API
		Texture2D(const TexOptions& options,
			unsigned int width, unsigned int height);
		MB_API
		Texture2D(const TexOptions& options, void* data,
			unsigned int width, unsigned int height);
		MB_API
		Texture2D(const TexOptions& options, const std::string src);
		virtual ~Texture2D(void);
	protected:
		std::string _src;
		unsigned int _width;
		unsigned int _height;

		void configTexture( void* data = nullptr );
		virtual void load( void );
      	unsigned char* loadTexture( const char* fileName_,
	        unsigned int& width_,
	        unsigned int& height_ );
	};
}

#endif /* __MB_TEXTURE2D__ */
