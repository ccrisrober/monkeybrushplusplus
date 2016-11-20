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

#include "Color4.hpp"

namespace MB
{
	Color4::Color4(float r, float g, float b, float a)
	{
        this->_color = Vect4(r, g, b, a);
    }
	Color4::Color4(const Color3& color)
	: Color4(color.r(), color.g(), color.b())
	{

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
	Color4 Color4::fromColor3(const Color3& color)
	{
		return Color4(color);
	}
	Color4 Color4::lerp(const Color4& minColor, const Color4& maxColor, float alpha)
	{

		float r = minColor.r() + (maxColor.r() - minColor.r()) * alpha;
		float g = minColor.g() + (maxColor.g() - minColor.g()) * alpha;
		float b = minColor.b() + (maxColor.b() - minColor.b()) * alpha;
		float a = minColor.a() + (maxColor.a() - minColor.a()) * alpha;

		return Color4(r, g, b, a);
	}
}
