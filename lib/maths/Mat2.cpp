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

#include "Mat2.hpp"

namespace mb
{
    Mat2::Mat2()
    {
        static const float _ident[] = {
            1.0f, 0.0f,
            0.0f, 1.0f
        };
        this->_values = std::vector<float>(_ident, _ident + sizeof(_ident) / sizeof(float));
    }
    Mat2::Mat2(const std::vector<float> values)
    {
        this->_values = values;
    }
	std::ostream& operator<<(std::ostream& str, const Mat2& m)
	{
		str << "Mat2(\n";
		str << "\t" << m._values[0] << ", " << m._values[1] << ", \n";
		str << "\t" << m._values[2] << ", " << m._values[3] << "\n";
		str << ")";
		return str;
	}
}
