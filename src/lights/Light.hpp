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

#ifndef __MB_LIGHT__
#define __MB_LIGHT__

#include "../core/Color3.hpp"

namespace MB {
	class Light {
	public:
		Light()
		: _intensity(1.0f)
		, _enable(true)
		, _attenuation(Vect3(
            1.0f,        // Constant
            0.014f,      // Linear
            0.0007f      // Quadratic
        ))
        , _color(Color3(1.0f, 1.0f, 1.0f))
        , _specColor(Color3(1.0f, 1.0f, 1.0f))
		{
		}
		virtual ~Light() = 0;
		inline float intensity() const { return this->_intensity; }
		inline Vect3 attenuation() const { return this->_attenuation; }
        inline bool isEnable() const { return this->_enable; }
        Color3& color() const { return this->_color; }
        Color3& specColor() const { return this->_specColor; }
        void intensity(const float i)
		{
			this->_intensity = i;
		}
        void attenuation(const Vect3 att)
		{
			this->_attenuation = att;
		}
        void enabled(const bool e)
		{
			this->_enable = e;
        }
        void color(const Color3& c) {
            this->_color = c;
        }
        void specColor(const Color3& sc) {
            this->_specColor = sc;
        }

	protected:
		float _intensity;
		bool _enable;
		Vect3 _attenuation;
        Color3 _color;
        Color3 _specColor;
	}
}

#endif /* __MB_LIGHT__ */
