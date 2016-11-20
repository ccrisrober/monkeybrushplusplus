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
		Box2D(const Vect2& min = Vect2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()), 
			const Vect2& max = Vect2(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity()))
		{
			this->_min = min;
			this->_max = max;
			this->_center = Vect2::add(this->_min, this->_max).scale(0.5f);
		}
		/**
		* Return min Box2D position.
		* @return {Vect2}
		*/
		Vect2 min() const
		{
			return this->_min;
		}
		/**
		* Return max Box2D position.
		* @return {Vect2}
		*/
		Vect2 max() const
		{
			return this->_max;
		}
		/**
		* Return Box2D center.
		* @return {Vect2}
		*/
		Vect2 center() const
		{
			return this->_center;
		}
		/**
		* Return box size.
		* @return {Vect2}
		*/
		Vect2 size() const
		{
			return Vect2::sub(this->max(), this->min());
		}
		bool containtsPoint(const Vect2& p)
		{
			if (p.x() > this->_min.x() || p.x() < this->_max.x() ||
				p.y() > this->_min.y() || p.y() < this->_max.y())
			{
				return true;
			}
			return false;
		}
		/**
		* Check if owner box contains another box
		* @param  {Box2D} b: Another box
		* @return {boolean}
		*/
		bool containsBox(const Box2D& b)
		{
			if ((this->_min.x() <= b._min.x()) && (b._max.x() <= this->_max.x()) &&
			(this->_min.y() <= b._min.y()) && (b._max.y() <= this->_max.y()))
			{
				return true;
			}
			return false;
		}
		/**
		* Check if owner box intersect another box
		* @param  {Box2D} b: Another box
		* @return {boolean}
		*/
		bool intersectsBox(const Box2D& b)
		{
			if (b._max.x() < this->_min.x() || b._min.x() > this->_max.x() ||
				b._max.y() < this->_min.y() || b._min.y() > this->_max.y())
			{
				return false;
			}
			return true;
		}
		bool isEqual(const Box2D& b)
		{
			return b.min() == this->_min && b.max() == this->_max;
		}
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
