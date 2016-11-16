/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal
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

#include "Color4.hpp"

namespace MB
{
	Color4::Color4(float r, float g, float b, float a)
	{
        this->_color = Vect4(r, g, b, a);
    }
    float Color4::r() const
    {
        return this->_color.x();
    }
    float Color4::g() const
    {
        return this->_color.y();
    }
    float Color4::b() const
    {
        return this->_color.z();
    }
    float Color4::a() const
    {
        return this->_color.w();
    }
    void Color4::r(const float v)
    {
        this->_color.x(v);
    }
    void Color4::g(const float v)
    {
        this->_color.y(v);
    }
    void Color4::b(const float v)
    {
        this->_color.z(v);
    }
    void Color4::a(const float v)
    {
        this->_color.w(v);
    }
}
