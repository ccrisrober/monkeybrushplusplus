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

#include "SpotLight.hpp"

namespace MB
{
	SpotLight::SpotLight(const Vect3 pos, const Vect3 dir, float coff)
		: Light()
		, _position(pos)
		, _direction(dir)
		, _cutOff(coff)
	{

	}
	Vect3 SpotLight::position() const
	{
		return this->_position;
	}
	Vect3 SpotLight::direction() const
	{
		return this->_direction;
	}
	float SpotLight::cutOff() const
	{
		return this->_cutOff;
	}
	void SpotLight::position(const Vect3 pos)
	{
		this->_position = pos;
	}
	void SpotLight::direction(const Vect3 dir)
	{
		this->_direction = dir;
	}
	void SpotLight::cutOff(const float coff)
	{
		this->_cutOff = coff;
	}
}

