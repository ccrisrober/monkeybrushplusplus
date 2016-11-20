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

#ifndef __MB_CURVES__
#define __MB_CURVES__

#include "Vect2.hpp"
#include "Vect3.hpp"
#include "Mathf.hpp"
#include <vector>

namespace MB
{
	namespace curves
	{
		class Curve2D
		{
		public:
			virtual Vect2 evaluate(const float t) = 0;
		};
		class Curve3D
		{
		public:
			virtual Vect3 evaluate(const float t) = 0;
		};

		/**
		* Ellipse class.
		* @class Ellipse
		* Create an ellipse to the path which is centered at (x, y)
		* position with the radius starting at startAngle and ending
		* at endAngle going in the given direction by anticlockwise.
		*/
		class Ellipse : public Curve2D
		{
		public:
			/**
			* Ellipse constructor
			* @param {Vect2}   center      The center of the ellipse.
			* @param {Vect2}   radius      Ellipse major and minux radius.
			* @param {number}  startAngle  [description]
			* @param {number}  endAngle    [description]
			* @param {boolean} isClockwise if true, draws the ellipse
			*                              anticlockwise (counter-clockwise),
			*                              otherwise in a clockwise direction.
			*/
			Ellipse(const Vect2& center, const Vect2& radius, float startAngle, float endAngle, bool isClockwise)
			: Curve2D()
				, _center(center)
				, _radius(radius)
				, _startAngle(startAngle)
				, _endAngle(endAngle)
				, _isClockwise(isClockwise)
			{
			}
			/**
			* Return interpolate position based on ellipse definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vect2}    A new Vect2 interpolated position.
			*/
			virtual Vect2 evaluate(const float t)
			{
				float deltaAngle = this->_endAngle - this->_startAngle;
				if (deltaAngle < 0.0f) deltaAngle += Mathf::TWO_PI;
				if (deltaAngle > Mathf::TWO_PI) deltaAngle -= Mathf::TWO_PI;
				float angle = this->_isClockwise ? this->_endAngle + (1.0f - t) *
					(Mathf::TWO_PI - deltaAngle) : this->_startAngle + t * deltaAngle;

				float tx = this->_center.x() + this->_radius.x() * std::cos(angle);
				float ty = this->_center.y() + this->_radius.y() * std::sin(angle);
				return Vect2(tx, ty);
			}
		protected:
			Vect2 _center;
			Vect2 _radius;
			float _startAngle;
			float _endAngle;
			bool _isClockwise;
		};
		/**
		* LineCurve2D class.
		* @class LineCurve2D
		* Create an line from first 2D point to second.
		*/
		class Line2D: public Curve2D
		{
		public:
			/**
			* Line2D constructor.
			* @param {Vect2} x Minimum point.
			* @param {Vect2} y Maximum point.
			*/
			Line2D(const Vect2& x, const Vect2& y)
				: Curve2D()
			{
				this->_p1 = x;
				this->_p2 = y;
			};
			/**
			* Return interpolate position based on 2D line definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vect2}    A new Vect2 interpolated position.
			*/
			virtual Vect2 evaluate(const float t)
			{
				return Vect2::add(Vect2::sub(this->_p2, this->_p1).multByScalar(t), this->_p1);
			};
		protected:
			Vect2 _p1;
			Vect2 _p2;
		};
		/**
		* LineCurve3D class.
		* @class LineCurve3D
		* Create an line from first 3D point to second.
		*/
		class Line3D: public Curve3D
		{
		public:
			/**
			* Line3D constructor.
			* @param {Vect3} x Minimum point.
			* @param {Vect3} y Maximum point.
			*/
			Line3D(const Vect3& x, const Vect3& y)
				: Curve3D()
			{
				this->_p1 = x;
				this->_p2 = y;
			};
			/**
			* Return interpolate position based on 3D line definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vect3}    A new Vect3 interpolated position.
			*/
			virtual Vect3 evaluate(const float t)
			{
				return Vect3::add(Vect3::sub(this->_p2, this->_p1).multByScalar(t), (this->_p1));
			};
		protected:
			Vect3 _p1;
			Vect3 _p2;
		};
		/**
		* BezierCurve class
		* @class BezierCurve
		*
		* Create a cubic Bézier curve to the path. It requires
		* three points. The first two points are control points
		* and the third one is the end point.
		*/
		class CubicBezier: public Curve2D
		{
			/**
			* CubicBezier constructor
			* @param {Vect2} cpi  Starting point
			* @param {Vect2} cpp1 First control point
			* @param {Vect2} cpp2 Second control point
			* @param {Vect2} cpe  Ending point
			*/
			CubicBezier(const Vect2& cpi, const Vect2& cpp1, const Vect2& cpp2, const Vect2& cpe)
				: Curve2D()
			{
				this->_list.push_back(cpi);
				this->_list.push_back(cpp1);
				this->_list.push_back(cpp2);
				this->_list.push_back(cpe);
			}
			/**
			* Return interpolate position based on cubic bezier definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vect2}    A new Vect2 interpolated position.
			*/
			virtual Vect2 evaluate(const float t)
			{
				return Vect2(
					this->bezierCurveInterpolation(
						this->_list[0].x(), this->_list[1].x(), this->_list[2].x(), this->_list[3].x(), t),
					this->bezierCurveInterpolation(
						this->_list[0].y(), this->_list[1].y(), this->_list[2].y(), this->_list[3].y(), t)
				);
			}
		protected:
			std::vector<Vect2> _list;
			float bezierCurveInterpolation(const float p0, const float p1,
				const float p2, const float p3, const float t)
			{
				return (p0 * std::pow(1.0f - t, 3.0f)) +
					(3.0f * p1 * std::pow(1.0f - t, 2.0f) * t) +
					(3.0f * p2 * t * t * (1.0f - t)) +
					(p3 * t * t * t);
			}
		};
		class CubicBezier3D: public Curve3D
		{
		public:
			/**
			* CubicBezier constructor
			* @param {Vect3} cpi  Starting point
			* @param {Vect3} cpp1 First control point
			* @param {Vect3} cpp2 Second control point
			* @param {Vect3} cpe  Ending point
			*/
			CubicBezier3D(const Vect3& cpi, const Vect3& cpp1, const Vect3& cpp2, const Vect3& cpe)
				: Curve3D()
			{
				this->_list.push_back(cpi);
				this->_list.push_back(cpp1);
				this->_list.push_back(cpp2);
				this->_list.push_back(cpe);
			}
			/**
			* Return interpolate position based on cubic bezier definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vect3}    A new Vect3 interpolated position.
			*/
			virtual Vect3 evaluate(const float t)
			{
				return Vect3(
					this->bezierCurveInterpolation(
						this->_list[0].x(), this->_list[1].x(), this->_list[2].x(), this->_list[3].x(), t),
					this->bezierCurveInterpolation(
						this->_list[0].y(), this->_list[1].y(), this->_list[2].y(), this->_list[3].y(), t),
					this->bezierCurveInterpolation(
						this->_list[0].z(), this->_list[1].z(), this->_list[2].z(), this->_list[3].z(), t)
				);
			}
		protected:
			std::vector<Vect3> _list;

			float bezierCurveInterpolation(const float p0, const float p1, 
				const float p2, const float p3, const float t)
			{
				return (p0 * std::pow(1.0 - t, 3.0f)) +
					(3.0f * p1 * std::pow(1.0f - t, 2.0f) * t) +
					(3.0f * p2 * t * t * (1.0f - t)) +
					(p3 * t * t * t);
			}
		};
		/**
		* QuadraticBezier class
		* @class QuadraticBezier
		*
		* Create a quadratic Bézier curve to the path.
		* It requires two points. The first point is a
		* control point and the second one is the end point.
		*/
		class QuadraticBezier2D: public Curve2D
		{
			/**
			* QuadraticBezier constructor.
			* @param {Vect2} cpi  Starting point.
			* @param {Vect2} cpp  Middle control point.
			* @param {Vect2} cpe  Ending point.
			*/
			QuadraticBezier2D(const Vect2& cpi, const Vect2& cpp, const Vect2& cpe)
				: Curve2D()
			{
				this->_list.push_back(cpi);
				this->_list.push_back(cpp);
				this->_list.push_back(cpe);
			}
			/**
			* Return interpolate position based on cubic bezier definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vect2}    A new Vect2 interpolated position.
			*/
			virtual Vect2 evaluate(const float t)
			{
				return Vect2(
					this->bezierCurveInterpolation(
						this->_list[0].x(), this->_list[1].x(), this->_list[2].x(), t),
					this->bezierCurveInterpolation(
						this->_list[0].y(), this->_list[1].y(), this->_list[2].y(), t)
				);
			}
		protected:
			std::vector<Vect2> _list;

			float bezierCurveInterpolation(const float p0, const float p1, const float p2, const float t)
			{
				return  (p0 * std::pow((1.0f - t), 2.0f)) +
				(2.0f * p1 * (1.0f - t) * t) +
				(p2 * std::pow(t, 2.0f));
			}
		};
		class QuadraticBezier3D: public Curve3D
		{
			/**
			* QuadraticBezier constructor.
			* @param {Vect3} cpi  Starting point.
			* @param {Vect3} cpp  Middle control point.
			* @param {Vect3} cpe  Ending point.
			*/
			QuadraticBezier3D(const Vect3& cpi, const Vect3& cpp, const Vect3& cpe)
				: Curve3D()
			{
				this->_list.push_back(cpi);
				this->_list.push_back(cpp);
				this->_list.push_back(cpe);
			}
			/**
			* Return interpolate position based on cubic bezier definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vect3}    A new Vect3 interpolated position.
			*/
			virtual Vect3 evaluate(const float t)
			{
				return Vect3(
					this->bezierCurveInterpolation(
						this->_list[0].x(), this->_list[1].x(), this->_list[2].x(), t),
					this->bezierCurveInterpolation(
						this->_list[0].y(), this->_list[1].y(), this->_list[2].y(), t),
					this->bezierCurveInterpolation(
						this->_list[0].z(), this->_list[1].z(), this->_list[2].z(), t)
				);
			}
		protected:
			std::vector<Vect3> _list;

			float bezierCurveInterpolation(const float p0, const float p1, const float p2, const float t)
			{
				return  (p0 * std::pow((1.0f - t), 2.0f)) +
				(2.0f * p1 * (1.0f - t) * t) +
				(p2 * std::pow(t, 2.0f));
			}
		};
	}
}

#endif /* __MB_CURVES__ */
