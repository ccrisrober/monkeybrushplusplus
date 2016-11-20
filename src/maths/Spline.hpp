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
#include "Interpolation.hpp"
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
			const std::vector<Vect2>& points = std::vector<Vect2>())
			: _intpMode(intpMode)
			, controlPoints(points)
		{
		}
		/**
		* Return interpolate point at t.
		* @param  {number} t Interpolation value [0, 1].
		* @return {Vect2}     Interpolated position.
		*/
		virtual Vect2 evaluate(const float t)
		{
			auto point = (this->controlPoints.size() - 1) * t;
			auto intPoint = std::floor(point);
			auto w = point - intPoint;

			Vect2 p0 = this->controlPoints[intPoint == 0 ? intPoint : intPoint - 1];
			Vect2 p1 = this->controlPoints[intPoint];
			Vect2 p2 = this->controlPoints[intPoint > this->controlPoints.size() - 2 ?
				this->controlPoints.size() - 1 : intPoint + 1];
			Vect2 p3 = this->controlPoints[intPoint > this->controlPoints.size() - 3 ?
				this->controlPoints.size() - 1 : intPoint + 2];

			switch (_intpMode)
			{
				case InterpolationMode::catmullRom:
					return Vect2(
						Interpolation::catmullRom(p0.x(), p1.x(), p2.x(), p3.x(), w),
						Interpolation::catmullRom(p0.y(), p1.y(), p2.y(), p3.y(), w)
					);
					break;
				case InterpolationMode::linear:
					return Vect2(
						Interpolation::linear(p0.x(), p3.x(), w),
						Interpolation::linear(p0.y(), p3.y(), w)
					);
					break;
				case InterpolationMode::bezier:
					return Vect2(
						Interpolation::bezier(p0.x(), p1.x(), p2.x(), p3.x(), w),
						Interpolation::bezier(p0.y(), p1.y(), p2.y(), p3.y(), w)
					);
					break;
			}
		}
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
			const std::vector<Vect3>& points = std::vector<Vect3>())
			: _intpMode(intpMode)
			, controlPoints(points)
		{
		}
		/**
		* Return interpolate point at t.
		* @param  {number} t Interpolation value [0, 1].
		* @return {Vect3}     Interpolated position.
		*/
		virtual Vect3 evaluate(const float t)
		{
			auto point = (this->controlPoints.size() - 1) * t;
			auto intPoint = std::floor(point);
			auto w = point - intPoint;

			Vect3 p0 = this->controlPoints[intPoint == 0 ? intPoint : intPoint - 1];
			Vect3 p1 = this->controlPoints[intPoint];
			Vect3 p2 = this->controlPoints[intPoint > this->controlPoints.size() - 2 ?
				this->controlPoints.size() - 1 : intPoint + 1];
			Vect3 p3 = this->controlPoints[intPoint > this->controlPoints.size() - 3 ?
				this->controlPoints.size() - 1 : intPoint + 2];

			switch (_intpMode)
			{
				case InterpolationMode::catmullRom:
					return Vect3(
						Interpolation::catmullRom(p0.x(), p1.x(), p2.x(), p3.x(), w),
						Interpolation::catmullRom(p0.y(), p1.y(), p2.y(), p3.y(), w),
						Interpolation::catmullRom(p0.z(), p1.z(), p2.z(), p3.z(), w)
					);
					break;
				case InterpolationMode::linear:
					return Vect3(
						Interpolation::linear(p0.x(), p3.x(), w),
						Interpolation::linear(p0.y(), p3.y(), w),
						Interpolation::linear(p0.z(), p3.z(), w)
					);
					break;
				case InterpolationMode::bezier:
					return Vect3(
						Interpolation::bezier(p0.x(), p1.x(), p2.x(), p3.x(), w),
						Interpolation::bezier(p0.y(), p1.y(), p2.y(), p3.y(), w),
						Interpolation::bezier(p0.z(), p1.z(), p2.z(), p3.z(), w)
					);
					break;
			}
		}
		Vect3 getTangent(const float oldDT, const float currentDT)
		{
			Vect3 p0 = this->evaluate(oldDT);
			Vect3 p1 = this->evaluate(currentDT);

			Vect3 s = Vect3::sub(p1, p0);
			s.normalize();

			return s;
		}
		float angleBetweenPoints(const float oldDT, const float currentDT)
		{
			Vect3 p0 = this->evaluate(oldDT);
			Vect3 p1 = this->evaluate(currentDT);

			float angle = std::atan2(p1.z() - p0.z(), p1.x() - p0.x());
			return Mathf::degToRad(angle);
		}
	protected:
		std::vector<Vect3> controlPoints;
		InterpolationMode _intpMode;
	};
}

#endif /* __MB_SPLINE__ */
