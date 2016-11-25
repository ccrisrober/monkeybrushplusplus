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

#include <mb/api.h>

#include <vector>

namespace MB
{
	class BufferAttribute
    {
	public:
		MB_API
		BufferAttribute(std::vector<float> arr, unsigned int size);
		MB_API
		void array(const std::vector<float> arr)
		{
			this->_arr = arr;
		}
		MB_API
        unsigned int size() const;
		MB_API
        std::vector<float> array() const;
		MB_API
        unsigned int count();
		MB_API
		unsigned int getX(unsigned int index);
		MB_API
		unsigned int getY(unsigned int index);
		MB_API
		unsigned int getZ(unsigned int index);
		MB_API
		unsigned int getW(unsigned int index);
		MB_API
		std::vector<float> getXY(unsigned int index);
		MB_API
		std::vector<float> getXYZ(unsigned int index);
		MB_API
		std::vector<float> getXYZW(unsigned int index);
		MB_API
		void setX(unsigned int index, float value);
		MB_API
		void setY(unsigned int index, float value);
		MB_API
		void setZ(unsigned int index, float value);
		MB_API
		void setW(unsigned int index, float value);
		MB_API
		void setXY(unsigned int index, float xValue, float yValue);
		MB_API
		void setXYZ(unsigned int index, float xValue, float yValue,
			float zValue);
		MB_API
		void setXYZW(unsigned int index, float xValue, float yValue,
			float zValue, float wValue);
	protected:
        std::vector<float> _arr;
        float _size;
    };
}

#endif /* __MB_BUFFER_ATTRIBUTE__ */
