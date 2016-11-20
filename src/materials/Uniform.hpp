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

#ifndef __MB_UNIFORM__
#define __MB_UNIFORM__

#include "../utils/any.hpp"

namespace MB
{
    typedef enum
    {
        Invalid, Float, Integer, Unsigned, Boolean, Vector2, Vector3, Vector4, Matrix2, Matrix3, Matrix4
    } UniformType;
    class Uniform {
    public:
        Uniform()
            : _type(Invalid)
            , _value()
        {
        }
        Uniform(UniformType type_, any value_ = nullptr)
            : _type(type_)
            , _value(value_)
            , _isDirty(true)
        {
        }
        Uniform(const Uniform& other)
            : _type(other._type), _value(other._value)
        {
        }
		any value() const {
			return this->_value;
		}
		UniformType type() const {
			return this->_type;
		}
		void value(const any v)
		{
			_isDirty = true;
			_value = std::move(v);
		}
		bool isDirty() const {
			return this->_isDirty;
		}
		void setDirty(const bool d)
		{
			_isDirty = d;
		}
    protected:
        UniformType _type;
        any _value;
        bool _isDirty;
    };
}

#endif /* __MB_UNIFORM__ */
