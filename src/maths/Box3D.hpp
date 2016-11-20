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

#ifndef __MB_BOX3D__
#define __MB_BOXD__

#include "Vect3.hpp"
#include <limits>

namespace MB
{
	class Box3D
	{
	public:
		/**
		* Box3D constructor
		* @param {Vect3 = new Vect3(Infinity, Infinity)} min: Box min corner
		* @param {Vect3 = new Vect3(-Infinity, Infinity)} max: Box max corner
		*/
		Box3D(const Vect3& min = Vect3::createFromScalar(std::numeric_limits<float>::infinity()),
			const Vect3& max = Vect3::createFromScalar(-std::numeric_limits<float>::infinity()))
		{
			this->_min = min;
			this->_max = max;
			this->_center = Vect3::add(this->_min, this->_max).scale(0.5f);
		}
		/**
		* Return min Box3D position.
		* @return {Vect3}
		*/
		Vect3 min() const
		{
			return this->_min;
		}
		/**
		* Return max Box3D position.
		* @return {Vect3}
		*/
		Vect3 max() const
		{
			return this->_max;
		}
		/**
		* Return Box3D center.
		* @return {Vect3}
		*/
		Vect3 center() const
		{
			return this->_center;
		}
		/**
		* Return box size.
		* @return {Vect3}
		*/
		Vect3 size() const
		{
			return Vect3::sub(this->max(), this->min());
		}
		bool containtsPoint(const Vect3& p)
		{
			if (p.x() > this->_min.x() || p.x() < this->_max.x() ||
				p.y() > this->_min.y() || p.y() < this->_max.y() ||
				p.z() > this->_min.z() || p.z() < this->_max.z())
			{
				return true;
			}
			return false;
		}
		/**
		* Check if owner box contains another box
		* @param  {Box3D} b: Another box
		* @return {boolean}
		*/
		bool containsBox(const Box3D& b)
		{
			if ((this->_min.x() <= b._min.x()) && (b._max.x() <= this->_max.x()) &&
				(this->_min.y() <= b._min.y()) && (b._max.y() <= this->_max.y()) &&
				(this->_min.z() <= b._min.z()) && (b._max.z() <= this->_max.z()))
			{
				return true;
			}
			return false;
		}
		/**
		* Check if owner box intersect another box
		* @param  {Box3D} b: Another box
		* @return {boolean}
		*/
		bool intersectsBox(const Box3D& b)
		{
			if (b._max.x() < this->_min.x() || b._min.x() > this->_max.x() ||
				b._max.y() < this->_min.y() || b._min.y() > this->_max.y() ||
				b._max.z() < this->_min.z() || b._min.z() > this->_max.z())
			{
				return false;
			}
			return true;
		}
		bool isEqual(const Box3D& b)
		{
			return b.min() == this->_min && b.max() == this->_max;
		}
	protected:
		/**
		* Min corner.
		* @type {Vect3}
		*/
		Vect3 _min;
		/**
		* Max corner.
		* @type {Vect3}
		*/
		Vect3 _max;
		/**
		* Box center.
		* @type {Vect3}
		*/
		Vect3 _center;
	};
}

#endif /* __MB_BOX3D__ */
