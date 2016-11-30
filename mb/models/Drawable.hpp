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

#ifndef __MB_DRAWABLE__
#define __MB_DRAWABLE__

#include <mb/api.h>

#include "../Includes.hpp"
#include "../core/VertexArray.hpp"
#include "../core/VertexBuffer.hpp"

namespace mb
{
    class Drawable
    {
    public:
        MB_API
        void render(unsigned int mode);
        MB_API
        unsigned int indicesLen() const;
		MB_API
		unsigned int verticesLen() const;
    protected:
        Drawable();
		unsigned int _numVertices;
		unsigned int _indicesLen;
		std::vector<VertexBuffer> _handle;
		VertexArray* _vao;
        void addBufferArray(unsigned int attribLocation, const std::vector<float>& data,
            unsigned int numElems, unsigned int type = GL_STATIC_DRAW);
    };
}

#endif /* __MB_DRAWABLE__ */
