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

#ifndef __MB_LIGHT__
#define __MB_LIGHT__

#include "../core/Color3.hpp"

namespace MB
{
	class Light
	{
	public:
		inline float intensity() const;
		inline Vect3 attenuation() const;
        inline bool isEnable() const;
        Color3 color() const;
        Color3 specColor() const;
        void intensity(const float i);
        void attenuation(const Vect3 att);
        void enabled(const bool e);
        void color(const Color3& c);
        void specColor(const Color3& sc);
	protected:
		Light();
		float _intensity;
		bool _enable;
		Vect3 _attenuation;
        Color3 _color;
        Color3 _specColor;
	};
}

#endif /* __MB_LIGHT__ */
