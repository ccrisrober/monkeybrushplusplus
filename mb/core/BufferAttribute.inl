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

#include "BufferAttribute.hpp"

namespace mb
{
  template<typename T>
  BufferAttribute<T>::BufferAttribute(std::vector<T> arr, unsigned int size)
    : _arr(arr)
    , _size(size)
  {
  }
  template<typename T>
  void BufferAttribute<T>::array(const std::vector<T> arr)
  {
    this->_arr = arr;
  }
  template<typename T>
  unsigned int BufferAttribute<T>::size() const
  {
    return this->_size;
  }
  template<typename T>
  std::vector<T> BufferAttribute<T>::array() const
  {
    return this->_arr;
  }
  template<typename T>
  unsigned int BufferAttribute<T>::count()
  {
    return this->_arr.size() / this->_size;
  }
  template<typename T>
  unsigned int BufferAttribute<T>::getX(unsigned int index)
  {
    if (this->_size < 1)
    {
      throw;
    }
    return this->_arr.at(index * this->_size);
  }
  template<typename T>
  unsigned int BufferAttribute<T>::getY(unsigned int index)
  {
    if (this->_size < 2)
    {
      throw;
    }
    return this->_arr.at(index * this->_size + 1);
  }
  template<typename T>
  unsigned int BufferAttribute<T>::getZ(unsigned int index)
  {
    if (this->_size < 3)
    {
      throw;
    }
    return this->_arr.at(index * this->_size + 2);
  }
  template<typename T>
  unsigned int BufferAttribute<T>::getW(unsigned int index)
  {
    if (this->_size < 4)
    {
      throw;
    }
    return this->_arr.at(index * this->_size + 3);
  }
  template<typename T>
  std::vector<T> BufferAttribute<T>::getXY(unsigned int index)
  {
    if (this->_size < 2)
    {
      throw;
    }
    index *= this->_size;

    return
    {
      this->_arr.at(index),
      this->_arr.at(index + 1)
    };
  }
  template<typename T>
  std::vector<T> BufferAttribute<T>::getXYZ(unsigned int index)
  {
    if (this->_size < 3)
    {
      throw;
    }
    index *= this->_size;

    return
    {
      this->_arr.at(index),
      this->_arr.at(index + 1),
      this->_arr.at(index + 2)
    };
  }
  template<typename T>
  std::vector<T> BufferAttribute<T>::getXYZW(unsigned int index)
  {
    if (this->_size < 4)
    {
      throw;
    }
    index *= this->_size;

    return
    {
      this->_arr.at(index),
      this->_arr.at(index + 1),
      this->_arr.at(index + 2),
      this->_arr.at(index + 3)
    };
  }
  template<typename T>
  void BufferAttribute<T>::setX(unsigned int index, T value)
  {
    if (this->_size < 1)
    {
      throw;
    }
    this->_arr[index * this->_size] = value;
  }
  template<typename T>
  void BufferAttribute<T>::setY(unsigned int index, T value)
  {
    if (this->_size < 2)
    {
      throw;
    }
    this->_arr[index * this->_size + 1] = value;
  }
  template<typename T>
  void BufferAttribute<T>::setZ(unsigned int index, T value)
  {
    if (this->_size < 3)
    {
      throw;
    }
    this->_arr[index * this->_size + 2] = value;
  }
  template<typename T>
  void BufferAttribute<T>::setW(unsigned int index, T value)
  {
    if (this->_size < 4)
    {
      throw;
    }
    this->_arr[index * this->_size + 3] = value;
  }
  template<typename T>
  void BufferAttribute<T>::setXY(unsigned int index, T xValue, T yValue)
  {
    if (this->_size < 2)
    {
      throw;
    }

    index *= this->_size;

    this->_arr[index] = xValue;
    this->_arr[index + 1] = yValue;
  }
  template<typename T>
  void BufferAttribute<T>::setXYZ(unsigned int index, T xValue, T yValue,
    T zValue)
  {
    if (this->_size < 3)
    {
      throw;
    }

    index *= this->_size;

    this->_arr[index] = xValue;
    this->_arr[index + 1] = yValue;
    this->_arr[index + 2] = zValue;
  }
  template<typename T>
  void BufferAttribute<T>::setXYZW(unsigned int index, T xValue, T yValue,
    T zValue, T wValue)
  {
    if (this->_size < 4)
    {
      throw;
    }

    index *= this->_size;

    this->_arr[index] = xValue;
    this->_arr[index + 1] = yValue;
    this->_arr[index + 2] = zValue;
    this->_arr[index + 3] = wValue;
  }
}
