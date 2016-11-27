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

#include "BufferAttribute.hpp"

namespace MB
{
	BufferAttribute::BufferAttribute(std::vector<float> arr, unsigned int size)
    : _arr(arr)
    , _size(size)
    {
    }
	void BufferAttribute::array(const std::vector<float> arr)
	{
		this->_arr = arr;
	}
    unsigned int BufferAttribute::size() const 
    {
        return this->_size;
    }
    std::vector<float> BufferAttribute::array() const 
    {
        return this->_arr;
    }
    unsigned int BufferAttribute::count()
    {
        return this->_arr.size() / this->_size;
    }
	unsigned int BufferAttribute::getX(unsigned int index)
	{
		if (this->_size < 1)
			throw;
		return this->_arr.at(index * this->_size);
	}
	unsigned int BufferAttribute::getY(unsigned int index)
	{
		if (this->_size < 2)
			throw;
		return this->_arr.at(index * this->_size + 1);
	}
	unsigned int BufferAttribute::getZ(unsigned int index)
	{
		if (this->_size < 3)
			throw;
		return this->_arr.at(index * this->_size + 2);
	}
	unsigned int BufferAttribute::getW(unsigned int index)
	{
		if (this->_size < 4)
			throw;
		return this->_arr.at(index * this->_size + 3);
	}
	std::vector<float> BufferAttribute::getXY(unsigned int index)
	{
		if (this->_size < 2)
			throw;
		index *= this->_size;

		return{
			this->_arr.at(index),
			this->_arr.at(index + 1)
		};
	}
	std::vector<float> BufferAttribute::getXYZ(unsigned int index)
	{
		if (this->_size < 3)
			throw;
		index *= this->_size;

		return{
			this->_arr.at(index),
			this->_arr.at(index + 1),
			this->_arr.at(index + 2)
		};
	}
	std::vector<float> BufferAttribute::getXYZW(unsigned int index)
	{
		if (this->_size < 4)
			throw;
		index *= this->_size;

		return{
			this->_arr.at(index),
			this->_arr.at(index + 1),
			this->_arr.at(index + 2),
			this->_arr.at(index + 3)
		};
	}
	void BufferAttribute::setX(unsigned int index, float value)
	{
		if (this->_size < 1)
			throw;
		this->_arr[index * this->_size] = value;
	}
	void BufferAttribute::setY(unsigned int index, float value)
	{
		if (this->_size < 2)
			throw;
		this->_arr[index * this->_size + 1] = value;
	}
	void BufferAttribute::setZ(unsigned int index, float value)
	{
		if (this->_size < 3)
			throw;
		this->_arr[index * this->_size + 2] = value;
	}
	void BufferAttribute::setW(unsigned int index, float value)
	{
		if (this->_size < 4)
			throw;
		this->_arr[index * this->_size + 3] = value;
	}
	void BufferAttribute::setXY(unsigned int index, float xValue, float yValue)
	{
		if (this->_size < 2)
			throw;
		index *= this->_size;
		this->_arr[index] = xValue;
		this->_arr[index + 1] = yValue;
	}
	void BufferAttribute::setXYZ(unsigned int index, float xValue, float yValue,
		float zValue)
	{
		if (this->_size < 3)
			throw;
		index *= this->_size;
		this->_arr[index] = xValue;
		this->_arr[index + 1] = yValue;
		this->_arr[index + 2] = zValue;
	}
	void BufferAttribute::setXYZW(unsigned int index, float xValue, float yValue,
		float zValue, float wValue)
	{
		if (this->_size < 4)
			throw;
		index *= this->_size;
		this->_arr[index] = xValue;
		this->_arr[index + 1] = yValue;
		this->_arr[index + 2] = zValue;
		this->_arr[index + 3] = wValue;
	}
}
