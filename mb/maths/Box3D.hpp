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
#define __MB_BOX3D__

#include <mb/api.h>

#include "Vect3.hpp"
#include <limits>

namespace mb
{
	class Box3D
	{
	public:
		/**
		* Box3D constructor
		* @param {Vect3 = new Vect3(Infinity, Infinity)} min: Box min corner
		* @param {Vect3 = new Vect3(-Infinity, Infinity)} max: Box max corner
		*/
		MB_API
		Box3D(const Vect3& min = Vect3::createFromScalar(std::numeric_limits<float>::infinity()),
			const Vect3& max = Vect3::createFromScalar(-std::numeric_limits<float>::infinity()));
		/**
		* Return min Box3D position.
		* @return {Vect3}
		*/
		MB_API
		Vect3 min() const;
		/**
		* Return max Box3D position.
		* @return {Vect3}
		*/
		MB_API
		Vect3 max() const;
		/**
		* Return Box3D center.
		* @return {Vect3}
		*/
		MB_API
		Vect3 center() const;
		/**
		* Return box size.
		* @return {Vect3}
		*/
		MB_API
		Vect3 size() const;
		MB_API
		bool containtsPoint(const Vect3& p);
		/**
		* Check if owner box contains another box
		* @param  {Box3D} b: Another box
		* @return {boolean}
		*/
		MB_API
		bool containsBox(const Box3D& b);
		/**
		* Check if owner box intersect another box
		* @param  {Box3D} b: Another box
		* @return {boolean}
		*/
		MB_API
		bool intersectsBox(const Box3D& b);
		MB_API
		bool isEqual(const Box3D& b);


		MB_API
		static Box3D createFromValues(const std::vector<float>& arr)
		{
			Vect3 min(std::numeric_limits<float>::infinity());
			Vect3 max(-std::numeric_limits<float>::infinity());

			float x, y, z;
			for (unsigned int i = 0, l = arr.size(); i < l; i += 3)
			{
				x = arr[i];
				y = arr[i + 1];
				z = arr[i + 2];

				if (x < min.x()) min.x(x);
				if (y < min.y()) min.y(y);
				if (z < min.z()) min.z(z);

				if (x > max.x()) max.x(x);
				if (y > max.y()) max.y(y);
				if (z > max.z()) max.z(z);
			}
			
			return Box3D(min, max);
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
