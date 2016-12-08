/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 * <https://github.com/maldicion069/monkeybrushplusplus>
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
#include "Light.hpp"

namespace mb
{
  Light::Light()
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
  inline float Light::intensity() const
  {
    return this->_intensity;
  }
  inline Vect3 Light::attenuation() const
  {
    return this->_attenuation;
  }
  inline bool Light::isEnable() const
  {
    return this->_enable;
  }
  Color3 Light::color() const
  {
    return this->_color;
  }
  Color3 Light::specColor() const
  {
    return this->_specColor;
  }
  void Light::intensity(const float i)
  {
    this->_intensity = i;
  }
    void Light::attenuation(const Vect3 att)
  {
    this->_attenuation = att;
  }
  void Light::enabled(const bool e)
  {
    this->_enable = e;
  }
  void Light::color(const Color3& c)
  {
    this->_color = c;
  }
  void Light::specColor(const Color3& sc)
  {
    this->_specColor = sc;
  }
}
