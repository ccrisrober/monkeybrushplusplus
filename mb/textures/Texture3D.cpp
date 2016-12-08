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

#include "Texture3D.hpp"

namespace mb
{
  Texture3D::Texture3D(const TexOptions& options, void* data,
    unsigned int width, unsigned int height, unsigned int depth) :
    Texture(options, GL_TEXTURE_3D)
  {
    this->load();
    glTexImage3D(
      this->_target,
      this->_level,
      this->_internalFormat,
      width,
      height,
      depth,
      0,
      this->_format,
      this->_type,
      data
    );
    glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER,
      static_cast<int>(this->_minFilter));
    glTexParameteri(this->_target, GL_TEXTURE_MAG_FILTER,
      static_cast<int>(this->_magFilter));
    glTexParameteri(this->_target, GL_TEXTURE_WRAP_S,
      static_cast<int>(this->_wrapS));
    glTexParameteri(this->_target, GL_TEXTURE_WRAP_T,
      static_cast<int>(this->_wrapT));
    glTexParameteri(this->_target, GL_TEXTURE_WRAP_R,
      static_cast<int>(this->_wrapR));

    // Set the mipmap levels (base and max)
    glTexParameteri(this->_target, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(this->_target, GL_TEXTURE_MAX_LEVEL, 4);

    if (options.autoMipmap)
    {
        glGenerateMipmap( this->_target );
    }

    this->unbind();
  }
  Texture3D::~Texture3D(void)
  {
  }
  void Texture3D::load(void)
  {
    if (!this->_loaded)
    {
      glGenTextures(1, &this->_handler);
      glBindTexture(this->_target, this->_handler);
      this->_loaded = true;
    }
  }
  void Texture3D::update(void* data, unsigned int width, unsigned int height,
    unsigned int depth)
  {
    this->load();
    glTexImage3D(
      this->_target,
      this->_level,
      this->_internalFormat,
      width,
      height,
      depth,
      0,
      this->_format,
      this->_type,
      data
    );
    this->unbind();
  }
}
