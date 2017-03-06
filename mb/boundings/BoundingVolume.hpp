/*
 * Copyright (c) 2017 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 * <https://github.com/maldicion069/monkeybrushplusplus>
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

#ifndef __MB_BOUNDING_VOLUME__
#define __MB_BOUNDING_VOLUME__

#include <mb/api.h>
#include <cmath>

namespace mb
{
	class BoundingVolume
	{
	protected:
		BoundingVolume( void );

	public:
		MB_API
		virtual ~BoundingVolume( void );
		MB_API
		const mb::Vect3 &getMin( void ) const { return _min; }
		MB_API
		const mb::Vect3 &getMax( void ) const { return _max; }
	protected:
		void setMax( const mb::Vect3& min ) { _min = min; }
		void setMin( const mb::Vect3& max ) { _max = max; }

	private:
		mb::Vect3 _min;
		mb::Vect3 _max;

	public:
		virtual bool testIntersection( const mb::Ray& ray ) const = 0;
	}
};

#endif /* __MB_BOUNDING_VOLUME__ */