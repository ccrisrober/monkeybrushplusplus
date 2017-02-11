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

#ifndef __MB_VERTEXARRAY__
#define __MB_VERTEXARRAY__

#include <mb/api.h>

#include "../Includes.hpp"
#include "Program.hpp"

namespace mb
{
  class VertexUBO
  {
  public:
    MB_API
    VertexUBO(const Program& prog, const char* name, unsigned int blockBindIdx);
    MB_API
    virtual ~VertexUBO( void );
    void bind( void );
    MB_API
    void update(const std::vector<float>& data);
    MB_API
    void unbind( void );
  protected:
    unsigned int _handler;
    unsigned int _index;
    const char* _name;
  };
}

#endif /* __MB_VERTEX_UBO_ */
