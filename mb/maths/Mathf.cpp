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

#include "Mathf.hpp"

namespace mb
{
    float Mathf::lerp(float x, float x1, float x2, float q00, float q01)
    {
        return ((x2 - x) / (x2 - x1)) * q00 + ((x - x1) / (x2 - x1)) * q01;
    }
    float Mathf::biLerp(float x, float y, float q11, float q12, 
    	float q21, float q22, float x1, float x2, float y1, float y2)
    {
        float r1 = lerp(x, x1, x2, q11, q21);
        float r2 = lerp(x, x1, x2, q12, q22);
        return lerp(y, y1, y2, r1, r2);
    }
    float Mathf::triLerp(float x, float y, float z, float q000,
        float q001, float q010, float q011, float q100, float q101,
        float q110, float q111, float x1, float x2, float y1, float y2,
        float z1, float z2)
    {
        float x00 = lerp(x, x1, x2, q000, q100);
        float x10 = lerp(x, x1, x2, q010, q110);
        float x01 = lerp(x, x1, x2, q001, q101);
        float x11 = lerp(x, x1, x2, q011, q111);
        float r0 = lerp(y, y1, y2, x00, x01);
        float r1 = lerp(y, y1, y2, x10, x11);

        return lerp(z, z1, z2, r0, r1);
    }
    float Mathf::degToRad(float degs)
    {
        return degs * Deg2Rad;
    }
    float Mathf::radToDeg(float rads)
    {
        return rads * Rad2Deg;
    }
    bool Mathf::isPOT(unsigned int v)
    {
        return (v & (v - 1)) == 0 && v != 0;
    }
    unsigned int Mathf::nearestPOT(unsigned int v)
    {
        return std::pow(2, std::round(std::log(v) / std::log(2)));
    }
    float Mathf::clamp(float v, float min, float max)
    {
        return std::min(max, std::max(min, v));
    }
    float Mathf::clamp01(float v)
    {
        return std::min(1.0f, std::max(0.0f, v));
    }
    int Mathf::sign(int v)
    {
        if (v == 0)
        {
            return v;
        }
        return (v > 0) ? 1 : -1;
    }
    float Mathf::normalizeAngle(float radAngle)
    {
	    float twoPi = 2.0f * PI;
	    return radAngle - twoPi * std::floor(radAngle / twoPi);
    }
    float Mathf::smoothstep(float x, float min, float max)
    {
        if (x <= min) return 0.0f;
        if (x >= max) return 1.0f;

        x = (x - min) / (max - min);

        return x * x * (3.0f - 2.0f * x);
    }
    float Mathf::smootherstep(float x, float min, float max)
    {
        if (x <= min) return 0.0f;
        if (x >= max) return 1.0f;
        x = (x - min) / (max - min);
        return std::pow(x, 3.0f) * (x * (x * 6.0f - 15.0f) + 10.0f);
    }
    std::string Mathf::toHex(/*n*/)
    {
        /*let str = n.toString(16);
        if (n <= 15) {
            return ("0" + str).toUpperCase();
        }
        return str.toUpperCase();*/
        return "";
    }
    float Mathf::angleBetween2DPoints(Vect2 /*p0*/, Vect2 /*p1*/)
    {
    	throw;
        //auto delta = Vect2.sub(p1, p0);
        //return std::atan2(delta.y, delta.x);
    }
    unsigned int Mathf::euclideanModulo(int /*m*/, unsigned int /*n*/)
    {
    	throw;
        //return m >= 0 ?
        //	m % n :
        //    (n - std::abs(m % n)) % n;
    }
    float Mathf::angleBetween3DPoints(Vect3 /*p0*/, Vect3 /*p1*/)
    {
    	throw;
        //Vect3 delta = Vect3.sub(p1, p0);
        //return std::atan2(delta.z(), delta.x());
    }
    Vect2 Mathf::CatmullRom2D(Vect2 p0, Vect2 p1, Vect2 p2, Vect2 p3, float t)
    {
        float t2 = t * t;
        float t3 = t * t2;

        float x = 0.5f * ((((2.0f * p1.x()) + ((-p0.x() + p2.x()) * t)) +
            (((((2.0 * p0.x()) - (5.0f * p1.x())) + (4.0f * p2.x())) - p3.x()) * t2)) +
            ((((-p0.x() + (3.0f * p1.x())) - (3.0f * p2.x())) + p3.x()) * t3));

        float y = 0.5f * ((((2.0f * p1.y()) + ((-p0.y() + p2.y()) * t)) +
            (((((2.0f * p0.y()) - (5.0f * p1.y())) + (4.0f * p2.y())) - p3.y()) * t2)) +
            ((((-p0.y() + (3.0f * p1.y())) - (3.0f * p2.y())) + p3.y()) * t3));

        return Vect2(x, y);
    }
    Vect2 Mathf::Hermite2D(Vect2 p0, Vect3 t0, Vect2 p1, Vect2 t1, float t)
    {
        float t2 = t * t;
        float t3 = t * t2;

        float part1 = ((2.0f * t3) - (3.0f * t2)) + 1.0f;
        float part2 = (-2.0f * t3) + (3.0f * t2);
        float part3 = (t3 - (2.0f * t2)) + t;
        float part4 = t3 - t2;

        float x = (((p0.x() * part1) + (p1.x() * part2)) + (t0.x() * part3)) + (t1.x() * part4);
        float y = (((p0.y() * part1) + (p1.y() * part2)) + (t0.y() * part3)) + (t1.y() * part4);

        return Vect2(x, y);
    }
    Vect3 Mathf::CatmullRom3D(Vect3 p0, Vect3 p1, Vect3 p2, Vect3 p3, float t)
    {
        float t2 = t * t;
        float t3 = t * t2;

        float x = 0.5f * ((((2.0f * p1.x()) + ((-p0.x() + p2.x()) * t)) +
            (((((2.0f * p0.x()) - (5.0f * p1.x())) + (4.0f * p2.x())) - p3.x()) * t2)) +
            ((((-p0.x() + (3.0f * p1.x())) - (3.0f * p2.x())) + p3.x()) * t3));

        float y = 0.5f * ((((2.0f * p1.y()) + ((-p0.y() + p2.y()) * t)) +
            (((((2.0f * p0.y()) - (5.0f * p1.y())) + (4.0f * p2.y())) - p3.y()) * t2)) +
            ((((-p0.y() + (3.0f * p1.y())) - (3.0f * p2.y())) + p3.y()) * t3));

        float z = 0.5f * ((((2.0f * p1.z()) + ((-p0.z() + p2.z()) * t)) +
            (((((2.0f * p0.z()) - (5.0f * p1.z())) + (4.0f * p2.z())) - p3.z()) * t2)) +
            ((((-p0.z() + (3.0f * p1.z())) - (3.0f * p2.z())) + p3.z()) * t3));

        return Vect3(x, y, z);
    }
    Vect3 Mathf::Hermite3D(Vect3 p0, Vect3 t0, Vect3 p1, Vect3 t1, float t)
    {
        float t2 = t * t;
        float t3 = t * t2;

        float part1 = ((2.0f * t3) - (3.0f * t2)) + 1.0f;
        float part2 = (-2.0f * t3) + (3.0f * t2);
        float part3 = (t3 - (2.0f * t2)) + t;
        float part4 = t3 - t2;

        float x = (((p0.x() * part1) + (p1.x() * part2)) + (t0.x() * part3)) + (t1.x() * part4);
        float y = (((p0.y() * part1) + (p1.y() * part2)) + (t0.y() * part3)) + (t1.y() * part4);
        float z = (((p0.z() * part1) + (p1.z() * part2)) + (t0.z() * part3)) + (t1.z() * part4);

        return Vect3(x, y, z);
    }
   	const float Mathf::PI = 3.1415f;
	const float Mathf::PI_2 = PI / 2.0f;
	const float Mathf::TWO_PI = 2.0f * PI;
   	const float Mathf::Deg2Rad = PI / 180.0f;
   	const float Mathf::Rad2Deg = 180.0f / PI;
}
