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

#ifndef __MB_BUFFER_ATTRIBUTE__
#define __MB_BUFFER_ATTRIBUTE__

#include 

namespace MB
{
	class BufferAttribute
    {
	public:
		BufferAttribute(std::vector<float> arr, unsigned int size)
        : _arr(arr)
        , _size(size)
        {
        }
        unsigned int size() const 
        {
            return this->_size;
        }
        std::vector<float> array() const 
        {
            return this->_arr;
        }
        unsigned int count()
        {
            return this->_arr.size() / this->_size;
        }
        unsigned int getX(unsigned int index)
        {
            if (this._size < 1)
                throw;
        }
	protected:
        std::vector<float> _arr;
        float _size;
    };
}

#endif /* __MB_BUFFER_ATTRIBUTE__ */
