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

#ifndef __MB__PRISM__
#define __MB__PRISM__

#include "Cone.hpp"

namespace MB
{
    class Prism: public Cone
    {
    public:
        /**
         * Prism constructor.
         * @param {number} radius: Prism radius
         * @param {number} height: Prism height
         * @param {number = 1} sides: Number of sides of the prism
         * @param {number = 1} heightSubDiv Height subdivisions
         * @param {boolean = true} createTopBase: Create top base
         * @param {boolean = true} createBottomBase: Create bottom base
         */
        Prism(float radius, float height, unsigned int sides,
            unsigned int heightSubDiv = 1, bool topCap = true, bool bottomCap = true)
        : Cone(radius, radius, height, sides, heightSubDiv, topCap, bottomCap)
        { }
	};
}

#endif /* __MB__PRISM__ */
