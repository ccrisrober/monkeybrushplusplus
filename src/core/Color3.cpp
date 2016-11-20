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

#include "Color3.hpp"

namespace MB
{
	Color3::Color3(float r, float g, float b)
	{
        this->_color = Vect3(r, g, b);
    }
	Color3::Color3(const Color3& c)
	{
		this->_color = c._color;
	}
	Color3& Color3::operator=(const Color3& c)
	{
		return copy(c);
	}
	Color3& Color3::copy(const Color3& c)
	{
		r(c.r());
		g(c.g());
		b(c.b());
		return *this;
	}
	Color3 Color3::createFromHSV(float h, float s, float v)
	{
		float r, g, b;
		if (v == 0.0f)
		{
			r = g = b = 0.0f;
		}
		else
		{
			int i = (int)std::floor(h * 6.0f);
			float f = (h * 6.0f) - i;
			float p = v * (1.0f - s);
			float q = v * (1.0f - (s * f));
			float t = v * (1.0f - (s * (1.0f - f)));

			switch (i)
			{
				case 0:
					r = v;
					g = t;
					b = p;
					break;
				case 1:
					r = q;
					g = v;
					b = p;
					break;
				case 2:
					r = p;
					g = v;
					b = t;
					break;
				case 3:
					r = p;
					g = q;
					b = v;
					break;
				case 4:
					r = t;
					g = p;
					b = v;
					break;
				case 5:
				default:
					r = v;
					g = p;
					b = q;
					break;
			}
		}
		return Color3(r, g, b);
	}
	Color3 Color3::lerp(const Color3& minColor, const Color3& maxColor, float alpha)
	{

		float r = minColor.r() + (maxColor.r() - minColor.r()) * alpha;
		float g = minColor.g() + (maxColor.g() - minColor.g()) * alpha;
		float b = minColor.b() + (maxColor.b() - minColor.b()) * alpha;

		return Color3(r, g, b);
	}
	Color3& Color3::gammaToLinear(const float& gammaFactor)
	{
		this->r(std::pow(this->r(), gammaFactor));
		this->g(std::pow(this->g(), gammaFactor));
		this->b(std::pow(this->b(), gammaFactor));

		return *this;
	}
	Color3& Color3::linearToGamma(const float& gammaFactor)
	{
		float invGamma = (gammaFactor > 0.0f) ? (1.0f / gammaFactor) : 1.0f;

		this->r(std::pow(this->r(), invGamma));
		this->g(std::pow(this->g(), invGamma));
		this->b(std::pow(this->b(), invGamma));

		return *this;
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
