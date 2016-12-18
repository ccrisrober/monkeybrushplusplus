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

#include "RenderTarget.hpp"

namespace mb
{
  RenderTarget::RenderTarget(unsigned int width, unsigned int height,
    std::vector<mb::TexturePtr> textures)
  {
    _textures = textures;
    _fbo = new mb::Framebuffer(_textures, mb::Vect2(width, height), true);
  }
  std::vector<mb::TexturePtr> RenderTarget::textures() const
  {
    return _textures;
  }
  void RenderTarget::bindTextures()
  {
    _fbo->onlyBindTextures();
  }
  void RenderTarget::bind()
  {
    this->_fbo->bind();
  }
  void RenderTarget::unbind()
  {
    this->_fbo->unbind();
  }
  void RenderTarget::setSize(const unsigned int& w, const unsigned int& h)
  {
    _width = w;
    _height = h;
  }
}
