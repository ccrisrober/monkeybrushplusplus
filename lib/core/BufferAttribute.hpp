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

#ifndef __MB_BUFFER_ATTRIBUTE__
#define __MB_BUFFER_ATTRIBUTE__

#include <mb/api.h>

#include <vector>
// TODO: Using templates!!
namespace mb
{
  template <typename T>
  class BufferAttribute
  {
  public:
    BufferAttribute(std::vector<T> arr, unsigned int size);
    void array(const std::vector<T> arr);
    unsigned int size() const;
    std::vector<T> array() const;
    unsigned int count();
    unsigned int getX(unsigned int index);
    unsigned int getY(unsigned int index);
    unsigned int getZ(unsigned int index);
    unsigned int getW(unsigned int index);
    std::vector<T> getXY(unsigned int index);
    std::vector<T> getXYZ(unsigned int index);
    std::vector<T> getXYZW(unsigned int index);
    void setX(unsigned int index, T value);
    void setY(unsigned int index, T value);
    void setZ(unsigned int index, T value);
    void setW(unsigned int index, T value);
    void setXY(unsigned int index, T xValue, T yValue);
    void setXYZ(unsigned int index, T xValue, T yValue, T zValue);
    void setXYZW(unsigned int index, T xValue, T yValue,
      T zValue, T wValue);
  protected:
    std::vector<T> _arr;
    unsigned int _size;
  };
}

#include "BufferAttribute.inl"

#endif /* __MB_BUFFER_ATTRIBUTE__ */
