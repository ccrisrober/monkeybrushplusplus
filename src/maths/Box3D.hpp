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
			const Vect3& max = Vect3::createFromScalar(-std::numeric_limits<float>::infinity()));
		/**
		* Return min Box3D position.
		* @return {Vect3}
		*/
		Vect3 min() const;
		/**
		* Return max Box3D position.
		* @return {Vect3}
		*/
		Vect3 max() const;
		/**
		* Return Box3D center.
		* @return {Vect3}
		*/
		Vect3 center() const;
		/**
		* Return box size.
		* @return {Vect3}
		*/
		Vect3 size() const;
		bool containtsPoint(const Vect3& p);
		/**
		* Check if owner box contains another box
		* @param  {Box3D} b: Another box
		* @return {boolean}
		*/
		bool containsBox(const Box3D& b);
		/**
		* Check if owner box intersect another box
		* @param  {Box3D} b: Another box
		* @return {boolean}
		*/
		bool intersectsBox(const Box3D& b);
		bool isEqual(const Box3D& b);
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
