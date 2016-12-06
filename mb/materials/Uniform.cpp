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

#include "Uniform.hpp"

namespace mb
{
    Uniform::Uniform()
        : _type(Invalid)
        , _value()
		, _isDirty(true)
    {
    }
    Uniform::Uniform(UniformType type_, any value_)
        : _type(type_)
        , _value(value_)
        , _isDirty(true)
    {
    }
    Uniform::Uniform(const Uniform& other)
        : _type(other._type), _value(other._value), _isDirty(true)
    {
    }
	any Uniform::value() const
    {
		return this->_value;
	}
	UniformType Uniform::type() const
    {
		return this->_type;
	}
	void Uniform::value(const any v)
	{
		_isDirty = true;
		_value = std::move(v);
	}
	bool Uniform::isDirty() const
    {
		return this->_isDirty;
	}
	void Uniform::setDirty(const bool d)
	{
		_isDirty = d;
	}
}
