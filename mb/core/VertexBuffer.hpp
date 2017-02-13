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

#ifndef __MB_VERTEX_BUFFER__
#define __MB_VERTEX_BUFFER__

#include <mb/api.h>

#include "../Includes.hpp"

#include <vector>

namespace mb
{
  class VertexBuffer
  {
  public:
    MB_API
    VertexBuffer(unsigned int type = GL_ARRAY_BUFFER);
    MB_API
    virtual ~VertexBuffer( void );
    MB_API
    void bind( void );
    MB_API
    void bufferSubData(int offset, std::vector<float> _data);
    MB_API
    void data(std::vector<float> _data, unsigned int usage = GL_STATIC_DRAW);
    MB_API
    void data(std::vector<unsigned int> _data, unsigned int usage = GL_STATIC_DRAW);
    MB_API
    std::vector<float> getSubData(int size, int offset = 0);
    MB_API
    void attribDivisor(int position, int length, int divisor, const void* stride = 0);
    MB_API
    void vertexAttribPointer(int attribLocation, int numElems,
            unsigned int type, bool normalized = false,
            const void* stride = 0);
    MB_API
    void render(unsigned int mode, unsigned int size);
    MB_API
    unsigned int getBufferType( void ) const;
    MB_API
    unsigned int getBuffer( void ) const;
    void unbind();
  protected:
    unsigned int _handler;
    unsigned int _type;
  };
}

#endif /* __MB_VERTEX_BUFFER__ */
