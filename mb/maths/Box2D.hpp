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

#ifndef __MB_BOX2D__
#define __MB_BOX2D__

#include <mb/api.h>

#include "Vect2.hpp"
#include <limits>

namespace MB
{
	class Box2D
	{
	public:
		/**
		* Box2D constructor
		* @param {Vect2 = new Vect2(Infinity, Infinity)} min: Box min corner
		* @param {Vect2 = new Vect2(-Infinity, Infinity)} max: Box max corner
		*/
		MB_API
		Box2D(const Vect2& min = Vect2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()), 
			const Vect2& max = Vect2(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity()));
		/**
		* Return min Box2D position.
		* @return {Vect2}
		*/
		MB_API
		Vect2 min() const;
		/**
		* Return max Box2D position.
		* @return {Vect2}
		*/
		MB_API
		Vect2 max() const;
		/**
		* Return Box2D center.
		* @return {Vect2}
		*/
		MB_API
		Vect2 center() const;
		/**
		* Return box size.
		* @return {Vect2}
		*/
		MB_API
		Vect2 size() const;
		MB_API
		bool containtsPoint(const Vect2& p);
		/**
		* Check if owner box contains another box
		* @param  {Box2D} b: Another box
		* @return {boolean}
		*/
		MB_API
		bool containsBox(const Box2D& b);
		/**
		* Check if owner box intersect another box
		* @param  {Box2D} b: Another box
		* @return {boolean}
		*/
		MB_API
		bool intersectsBox(const Box2D& b);
		MB_API
		bool isEqual(const Box2D& b);
	protected:
		/**
		* Min corner.
		* @type {Vect2}
		*/
		Vect2 _min;
		/**
		* Max corner.
		* @type {Vect2}
		*/
		Vect2 _max;
		/**
		* Box center.
		* @type {Vect2}
		*/
		Vect2 _center;
	};
}

#endif /* __MB_BOX2D__ */
