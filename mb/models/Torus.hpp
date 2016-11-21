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

#ifndef __MB__TORUS__
#define __MB__TORUS__

#include <mb/api.h>

#include <functional>
#include "Drawable.hpp"
#include "../maths/Mathf.hpp"
#include "../core/BufferAttribute.hpp"

namespace MB
{
    class Torus: public Drawable
    {
    public:
        MB_API
        Torus(float outerRadius = 1.0f, float innerRadius = 0.5f,
            unsigned int sides = 4, unsigned int rings = 10);
    };
}

#endif /* __MB__TORUS__ */
