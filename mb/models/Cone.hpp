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

#ifndef __MB__CONE__
#define __MB__CONE__

#include <mb/api.h>

#include <functional>
#include "Drawable.hpp"
#include "../maths/Mathf.hpp"
#include "../core/BufferAttribute.hpp"

namespace MB
{
    class Cone: public Drawable
    {
    public:
		MB_API
        Cone(float bottomRadius, float topRadius,
			float height, unsigned int radialSubDiv = 3, int heightSubDiv = 1,
			bool createTopBase = true, bool createBottomBase = true);
    };
}

#endif /* __MB__CONE__ */
