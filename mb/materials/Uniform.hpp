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

#ifndef __MB_UNIFORM__
#define __MB_UNIFORM__

#include <mb/api.h>

#include "../utils/any.hpp"

#include <vector>

namespace mb
{
  MB_API
  typedef enum
  {
    Invalid,
		Float, Integer, Unsigned, Boolean,
		Vector2, Vector3, Vector4,
		Matrix2, Matrix3, Matrix4,
		TextureSampler
  } UniformType;

  class Uniform
	{
  public:
    MB_API
    Uniform();
    MB_API
    Uniform(UniformType type_, any value_ = nullptr);
    MB_API
    Uniform(const Uniform& other);
    MB_API
		any value() const;
    MB_API
		UniformType type() const;
    MB_API
		void value(const any v);
    MB_API
		bool isDirty() const;
    MB_API
		void setDirty(const bool d);
  protected:
    UniformType _type;
    any _value;
    bool _isDirty;
  };

  class UniformsList
  {
  public:
    MB_API
    UniformsList()
    {
    }
    MB_API
    UniformsList& operator<<( const std::pair<const char*, mb::Uniform*>& u )
    {
      uniforms.push_back( u );
      return *this;
    }
    std::vector<std::pair<const char*, mb::Uniform*> > uniforms;
  };
}

#endif /* __MB_UNIFORM__ */
