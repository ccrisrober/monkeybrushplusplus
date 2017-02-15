/*
 * Copyright (c) 2017 maldicion069
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

#ifndef __MB_CUSTOM_MODEL__
#define __MB_CUSTOM_MODEL__

#include <mb/api.h>

#include "Drawable.hpp"
#include <vector>
#include "../maths/Mathf.hpp"
#include "../maths/Vect3.hpp"

namespace mb
{
    class CustomModel: public Drawable
    {
    public:
      MB_API
      CustomModel( )
      {
      }


      /*addBufferArray(0, vertices, 3, GL_STATIC_DRAW);
      addBufferArray(1, normals, 3, GL_STATIC_DRAW);
      addBufferArray(2, texCoords, 2, GL_STATIC_DRAW);
      std::vector<unsigned int> data = indices;
      unsigned int type = GL_STATIC_DRAW;
      //addElementArray(data, type);

      VertexBuffer vbIndices(GL_ELEMENT_ARRAY_BUFFER);
      vbIndices.data(data, type);
      _indicesLen = data.size();
      this->_handle.push_back(vbIndices);

      _vao->unbind();
      }
      MB_API
      void addAttribute( mb::BufferAttribute& ba )
      {
        if ( _vao != nullptr )
        {
          _vao = new VertexArray();
        }
        _vao->bind();


        _vao->unbind();
      }*/

    protected:

    };
}

#endif /* __MB_CUSTOM_MODEL__ */
