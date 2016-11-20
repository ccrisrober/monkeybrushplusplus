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

#include "Vect2.hpp"
#include "Vect3.hpp"
#include <vector>

namespace MB
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
		Spline2D(InterpolationMode intpMode = InterpolationMode::catmullRom, 
			const std::vector<Vect2>& points = std::vector<Vect2>());
		/**
		* Return interpolate point at t.
		* @param  {number} t Interpolation value [0, 1].
		* @return {Vect2}     Interpolated position.
		*/
		virtual Vect2 evaluate(const float t);
	protected:
		std::vector<Vect2> controlPoints;
		InterpolationMode _intpMode;
	};
	/**
	* Spline3D class
	* Create a smooth 3D spline curve from a points list.
	*
	* @class Spline3D
	*/
	class Spline3D
	{
		Spline3D(InterpolationMode intpMode = InterpolationMode::catmullRom,
			const std::vector<Vect3>& points = std::vector<Vect3>());
		/**
		* Return interpolate point at t.
		* @param  {number} t Interpolation value [0, 1].
		* @return {Vect3}     Interpolated position.
		*/
		virtual Vect3 evaluate(const float t);
		Vect3 getTangent(const float oldDT, const float currentDT);
		float angleBetweenPoints(const float oldDT, const float currentDT);
	protected:
		std::vector<Vect3> controlPoints;
		InterpolationMode _intpMode;
	};
}

#endif /* __MB_SPLINE__ */
