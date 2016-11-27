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

#ifndef __MB_SPLINE__
#define __MB_SPLINE__

#include <mb/api.h>

#include "Vect2.hpp"
#include "Vect3.hpp"
#include <vector>

namespace mb
{
	enum class InterpolationMode
	{
		catmullRom, linear, bezier
	};
	/**
	* Spline2D class
	* Create a smooth 2D spline curve from a points list.
	*
	* @class Spline2D
	*/
	class Spline2D
	{
	public:
		MB_API
		Spline2D(InterpolationMode intpMode = InterpolationMode::catmullRom, 
			const std::vector<Vect2>& points = std::vector<Vect2>());
		MB_API
		virtual ~Spline2D() {}
		/**
		* Return interpolate point at t.
		* @param  {number} t Interpolation value [0, 1].
		* @return {Vect2}     Interpolated position.
		*/
		virtual Vect2 evaluate(const float t);
	protected:
		InterpolationMode _intpMode;
		std::vector<Vect2> controlPoints;
	};
	/**
	* Spline3D class
	* Create a smooth 3D spline curve from a points list.
	*
	* @class Spline3D
	*/
	class Spline3D
	{
	public:
		MB_API
		Spline3D(InterpolationMode intpMode = InterpolationMode::catmullRom,
			const std::vector<Vect3>& points = std::vector<Vect3>());
		virtual ~Spline3D() {}
		/**
		* Return interpolate point at t.
		* @param  {number} t Interpolation value [0, 1].
		* @return {Vect3}     Interpolated position.
		*/
		MB_API
		virtual Vect3 evaluate(const float t);
		MB_API
		Vect3 getTangent(const float oldDT, const float currentDT);
		MB_API
		float angleBetweenPoints(const float oldDT, const float currentDT);
	protected:
		InterpolationMode _intpMode;
		std::vector<Vect3> controlPoints;
	};
}

#endif /* __MB_SPLINE__ */
