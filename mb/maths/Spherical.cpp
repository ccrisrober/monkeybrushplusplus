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

#include "Spherical.hpp"
#include "Mathf.hpp"
#include "float.h"

namespace mb
{
  Vect3 Spherical::toCartesian( )
  {
    return sphericalToCartesian(_radius, _polar, _elevation);
  }
  Spherical Spherical::cartesianToSpherical(Vect3 cartCoords)
  {
    if ( cartCoords.x( ) == 0.0f )
    {
      cartCoords.x( FLT_EPSILON );
    }
    Spherical res;
    res._radius = (float) sqrt((cartCoords.x( ) * cartCoords.x( ))
                + (cartCoords.y( ) * cartCoords.y( ))
                + (cartCoords.z( ) * cartCoords.z( )));
    res._polar = (float) atan(cartCoords.z( ) / cartCoords.x( ));
    if (cartCoords.x( ) < 0.0f)
    {
      res._polar += Mathf::PI;
    }
    res._elevation = (float) asin(cartCoords.y( ) / res._radius);
    return res;
  }
  Vect3 Spherical::sphericalToCartesian(float r, float p, float e)
  {
    float a = (float) (r * cos(e));
    return Vect3(
      (float) (a * cos(p)),
      (float) (r * sin(e)),
      (float) (a * sin(p))
    );
  }
}
