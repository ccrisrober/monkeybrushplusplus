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

#ifndef __MB_MATHF__
#define __MB_MATHF__

#include "Vect2.hpp"
#include "Vect3.hpp"
#include <cmath>
#include <algorithm>

namespace MB
{
	class Mathf
	{
	public:
        /**
         * Linear interpolation.
         * @param  {float} x   [description]
         * @param  {float} x1  [description]
         * @param  {float} x2  [description]
         * @param  {float} q00 [description]
         * @param  {float} q01 [description]
         * @return {float}     [description]
         */
        static float lerp(float x, float x1, float x2, float q00, float q01);
        /**
         * Bilinear interpolation
         * @param  {number} x   [description]
         * @param  {number} y   [description]
         * @param  {number} q11 [description]
         * @param  {number} q12 [description]
         * @param  {number} q21 [description]
         * @param  {number} q22 [description]
         * @param  {number} x1  [description]
         * @param  {number} x2  [description]
         * @param  {number} y1  [description]
         * @param  {number} y2  [description]
         * @return {number}     [description]
         */
        static float biLerp(float x, float y, float q11, float q12, 
        	float q21, float q22, float x1, float x2, float y1, float y2);
        /**
         * Trilinear interpolation.
         * @param  {number} x    [description]
         * @param  {number} y    [description]
         * @param  {number} z    [description]
         * @param  {number} q000 [description]
         * @param  {number} q001 [description]
         * @param  {number} q010 [description]
         * @param  {number} q011 [description]
         * @param  {number} q100 [description]
         * @param  {number} q101 [description]
         * @param  {number} q110 [description]
         * @param  {number} q111 [description]
         * @param  {number} x1   [description]
         * @param  {number} x2   [description]
         * @param  {number} y1   [description]
         * @param  {number} y2   [description]
         * @param  {number} z1   [description]
         * @param  {number} z2   [description]
         * @return {number}      [description]
         */
        static float triLerp(float x, float y, float z, float q000,
            float q001, float q010, float q011, float q100, float q101,
            float q110, float q111, float x1, float x2, float y1, float y2,
            float z1, float z2);
        /**
         * Converts degrees angle to radians angle.
         * @param  {number} degs Degrees angle
         * @return {number}      Radians angle
         */
        static float degToRad(float degs);
        /**
         * Converts radians angle to degrees angle.
         * @param  {number} degs Radians angle
         * @return {number}      Degrees angle
         */
        static float radToDeg(float rads);
        /**
         * Returns true if the value is power of two.
         * @param  {number} v Integer value.
         * @return {boolean}
         */
        static bool isPOT(unsigned int v);
        /**
         * Returns the next power of two value.
         * @param  {number} v Integer value.
         * @return {number}
         */
        static unsigned int nearestPOT(unsigned int v);
        /**
         * Clamps a value to be between a minimum and maximum value.
         * @param  {number} v   Value to clamp.
         * @param  {number} min Minimum value.
         * @param  {number} max Maximum value
         * @return {number}
         */
        static float clamp(float v, float min, float max);
        /**
         * Clamps value between 0 and 1 and returns value.
         * @param  {number} v Value to clamp.
         * @return {number}
         */
        static float clamp01(float v);
        /**
         * Return 1 when is a positive number. -1 otherwise.
         * @param  {number} v [description]
         * @return {number}   [description]
         */
        static int sign(int v);
        /**
         * Normalizes radians angle between [0, 2π].
         * @param  {number} radAngle Radian angle.
         * @return {number}          Normalizated radian angle.
         */
        static float normalizeAngle(float radAngle);
        /**
         * Interpolates between min and max with smoothing at the limits.
         * @param  {number}     x   Value to interpolate.
         * @param  {number = 0} min Minimum value.
         * @param  {number = 1} max Maximum value.
         * @return {number}         Interpolated value
         */
        static float smoothstep(float x, float min = 0.0f, float max = 1.0f);
        /**
         * Interpolates between min and max with more smoothing at the limits thatn smoothstep.
         * @param  {number}     x   Value to interpolate.
         * @param  {number = 0} min Minimum value.
         * @param  {number = 1} max Maximum value.
         * @return {number}         Interpolated value
         */
        static float smootherstep(float x, float min, float max);
        /**
         * Convert number to hexadecimal.
         * @param  {number} n Number value.
         * @return {string}   Hexadecimal representation.
         */
        static std::string toHex(/*n*/);
        /**
         * Return angle between two 2D points
         * @param  {Vect2}  p0 First 2D point.
         * @param  {Vect2}  p1 Second 2D point.
         * @return {number}    Radians angle between points.
         */
        static float angleBetween2DPoints(Vect2 /*p0*/, Vect2 /*p1*/);
        static unsigned int euclideanModulo(int /*m*/, unsigned int /*n*/);
        /**
         * Return angle between two 3D points
         * @param  {Vect3}  p0 First 3D point.
         * @param  {Vect3}  p1 Second 3D point.
         * @return {number}    Radians angle between points.
         */
        static float angleBetween3DPoints(Vect3 /*p0*/, Vect3 /*p1*/);
        /**
         * Evaluates CatmullRom spline in 2D.
         * @param  {Vect3}  p0 [description]
         * @param  {Vect3}  p1 [description]
         * @param  {Vect3}  p2 [description]
         * @param  {Vect3}  p3 [description]
         * @param  {number} t  [description]
         * @return {Vect3}     [description]
         */
        static Vect2 CatmullRom2D(Vect2 p0, Vect2 p1, Vect2 p2, Vect2 p3, float t);
        /**
         * Evaluates Hermite spline in 2D.
         * @param  {Vect2}  p0 [description]
         * @param  {Vect2}  t0 [description]
         * @param  {Vect2}  p1 [description]
         * @param  {Vect2}  t1 [description]
         * @param  {number} t  [description]
         * @return {Vect2}     [description]
         */
        static Vect2 Hermite2D(Vect2 p0, Vect3 t0, Vect2 p1, Vect2 t1, float t);
        /**
         * Evaluates CatmullRom spline in 3D.
         * @param  {Vect3}  p0 [description]
         * @param  {Vect3}  p1 [description]
         * @param  {Vect3}  p2 [description]
         * @param  {Vect3}  p3 [description]
         * @param  {number} t  [description]
         * @return {Vect3}     [description]
         */
        static Vect3 CatmullRom3D(Vect3 p0, Vect3 p1, Vect3 p2, Vect3 p3, float t);
        /**
         * Evaluates Hermite spline in 3D.
         * @param  {Vect3}  p0 [description]
         * @param  {Vect3}  t0 [description]
         * @param  {Vect3}  p1 [description]
         * @param  {Vect3}  t1 [description]
         * @param  {number} t  [description]
         * @return {Vect3}     [description]
         */
        static Vect3 Hermite3D(Vect3 p0, Vect3 t0, Vect3 p1, Vect3 t1, float t);
		static const float PI_2;
		static const float PI;
		static const float TWO_PI;
        static const float Deg2Rad;
        static const float Rad2Deg;
	};
}

#endif /* __MB_MATHF__ */