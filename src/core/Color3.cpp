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

#include "Color3.hpp"

namespace MB
{
	Color3::Color3(float r, float g, float b)
	{
        this->_color = Vect3(r, g, b);
    }
    float Color3::r() const
    {
        return this->_color.x();
    }
    float Color3::g() const
    {
        return this->_color.y();
    }
    float Color3::b() const
    {
        return this->_color.z();
    }
    void Color3::r(const float v)
    {
        this->_color.x(v);
    }
    void Color3::g(const float v)
    {
        this->_color.y(v);
    }
    void Color3::b(const float v)
    {
        this->_color.z(v);
    }
    Color3 Color3::createFromHex(int hex)
    {
        return Color3(
            (float)(hex >> 16 & 255) / 255.0f,
            (float)(hex >> 8 & 255) / 255.0f,
            (float)(hex & 255) / 255.0f
        );
    }

    Color3 Color3::Aqua = Color3::createFromHex(0x00FFFF);
    Color3 Color3::Beige = Color3::createFromHex(0xF5F5DC);
    Color3 Color3::Black = Color3::createFromHex(0x000000);
    Color3 Color3::Blue = Color3::createFromHex(0x0000FF);
    Color3 Color3::Brown = Color3::createFromHex(0xA52A2A);
    Color3 Color3::Cyan = Color3::createFromHex(0x00FFFF);
    Color3 Color3::Gold = Color3::createFromHex(0xFFD700);
    Color3 Color3::Green = Color3::createFromHex(0x008000);
    Color3 Color3::Indigo = Color3::createFromHex(0x4B0082);
    Color3 Color3::Lavender = Color3::createFromHex(0xE6E6FA);
    Color3 Color3::Orange = Color3::createFromHex(0xFFA500);
    Color3 Color3::Pink = Color3::createFromHex(0xFFC0CB);
    Color3 Color3::Purple = Color3::createFromHex(0x800080);
    Color3 Color3::Red = Color3::createFromHex(0xFF0000);
    Color3 Color3::Yellow = Color3::createFromHex(0xFFFF00);
    Color3 Color3::White = Color3::createFromHex(0xFFFFFF);
}
