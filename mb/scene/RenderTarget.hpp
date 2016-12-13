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

#ifndef __MB_RENDER_TARGET__
#define __MB_RENDER_TARGET__

#include <mb/api.h>

//#include "../core/GLContext.hpp"
#include "../core/Framebuffer.hpp"
#include "../textures/Texture2D.hpp"

namespace mb
{
  class RenderTarget
  {
  public:
    MB_API
    RenderTarget(unsigned int width, unsigned int height, std::vector<mb::Texture*> textures);
    MB_API
    std::vector<mb::Texture*> textures() const;
    MB_API
    void bindTextures();
    MB_API
    void bind();
    MB_API
    void unbind();
    MB_API
    void setSize(const unsigned int& w, const unsigned int& h);
  protected:
    unsigned int _width;
    unsigned int _height;
    mb::Framebuffer* _fbo;
    std::vector<mb::Texture*> _textures;

    //mb::GLContext* _context;
  };
}

#endif /* __MB_RENDER_TARGET__ */
