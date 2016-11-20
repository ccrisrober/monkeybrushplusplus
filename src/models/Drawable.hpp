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

#include "../Includes.hpp"
#include "../core/VertexArray.hpp"
#include "../core/VertexBuffer.hpp"

namespace MB
{
    class Drawable
    {
    public:
        void render()
        {
            this->_vao->bind();
            glDrawElements(GL_TRIANGLES, _indicesLen, GL_UNSIGNED_INT, 0);
            this->_vao->unbind();
        }
    protected:
        Drawable()
        {
            
        }
		unsigned int _indicesLen;
		std::vector<VertexBuffer> _handle;
		VertexArray* _vao;
        void addBufferArray(unsigned int attribLocation, const std::vector<float>& data,
            unsigned int numElems, unsigned int type = GL_STATIC_DRAW)
        {
            VertexBuffer vb(GL_ARRAY_BUFFER);
			vb.data(data, type);
			vb.vertexAttribPointer(attribLocation, numElems, GL_FLOAT, false);
            this->_handle.push_back(vb);
        }
    };
}

#endif /* __MB_DRAWABLE__ */
