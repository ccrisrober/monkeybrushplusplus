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

#include "HemisphericLight.hpp"

namespace mb
{
    HemisphericLight::HemisphericLight(const Vect3 dir)
    :Light()
    , _direction(dir)
    {
    }
    Vect3 HemisphericLight::direction() const
    {
        return this->_direction;
    }
    void HemisphericLight::direction(const Vect3& pos)
    {
        this->_direction = pos;
    }
    Color3 HemisphericLight::groundColor() const
    {
        return this->_groundColor;
    }
    void HemisphericLight::groundColor(const Color3& c)
    {
        this->_groundColor = c;
    }
}
