/*
* Copyright (c) 2016 maldicion069
*
* Authors: Cristian Rodríguez Bernal
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

#include "Vect3.hpp"
#include "../core/Color3.hpp"

namespace mb
{
	Vect3 Vect3::xAxis(1.0f, 0.0f, 0.0f);
	Vect3 Vect3::yAxis(0.0f, 1.0f, 0.0f);
	Vect3 Vect3::zAxis(0.0f, 0.0f, 1.0f);
	Vect3 Vect3::up(0.0f, 1.0f, 1.0f);
	Vect3::Vect3(float x, float y, float z)
	{
		this->_values.resize(3);
		this->_values[0] = x;
		this->_values[1] = y;
		this->_values[2] = z;
	}
	Vect3::Vect3(const Color3& color)
		: Vect3(color.r(), color.g(), color.b())
	{
	}
	float Vect3::x() const
	{
		return this->_values[0];
	}
	void Vect3::x(const float& v)
	{
		this->_values[0] = v;
	}
	float Vect3::y() const
	{
		return this->_values[1];
	}
	void Vect3::y(const float& v)
	{
		this->_values[1] = v;
	}
	float Vect3::z() const
	{
		return this->_values[2];
	}
	void Vect3::z(const float& v)
	{
		this->_values[2] = v;
	}
	Vect3 Vect3::createFromScalar(float value)
	{
		return Vect3(value, value, value);
	}
	// TODO: CONST&??
	void Vect3::set(float x_, float y_, float z_)
	{
		x(x_);
		y(y_);
		z(z_);
	}
	Vect3 Vect3::add(const Vect3& v)
	{
		Vect3 vv(
			this->_values[0] + v._values[0],
			this->_values[1] + v._values[1],
			this->_values[2] + v._values[2]
		);

		return vv;
	}
	Vect3 Vect3::sub(const Vect3& v)
	{
		Vect3 vv(
			this->_values[0] - v._values[0],
			this->_values[1] - v._values[1],
			this->_values[2] - v._values[2]
		);

		return vv;
	}
	Vect3 Vect3::sub(const Vect3& v1, const Vect3& v2)
	{
		Vect3 vv(
			v1._values[0] - v2._values[0],
			v1._values[1] - v2._values[1],
			v1._values[2] - v2._values[2]
		);

		return vv;
	}
	Vect3 Vect3::mult(const Vect3& v)
	{
		Vect3 vv(
			this->_values[0] * v._values[0],
			this->_values[1] * v._values[1],
			this->_values[2] * v._values[2]
		);

		return vv;
	}
	Vect3 Vect3::multByScalar(float s)
	{
		Vect3 vv(
			this->_values[0] * s,
			this->_values[1] * s,
			this->_values[2] * s
		);

		return vv;
	}
	Vect3 Vect3::div(const Vect3& v)
	{
		Vect3 vv(
			this->_values[0] / v._values[0],
			this->_values[1] / v._values[1],
			this->_values[2] / v._values[2]
		);

		return vv;
	}
	float Vect3::distance(const Vect3& v, const Vect3& v2)
	{
        return std::sqrt(squaredDistance(v, v2));
	}
	float Vect3::squaredDistance(const Vect3& v, const Vect3& v2)
	{
		Vect3 vsub = Vect3::sub(v2, v);;
        return (vsub._values[0] * vsub._values[0] + vsub._values[1] * vsub._values[1] +
                vsub._values[2] * vsub._values[2]);
	}
	Vect3 Vect3::cross(const Vect3& v, const Vect3& v2)
	{
		float
			x = v.x(),
			y = v.y(),
			z = v.z();

		float
			x2 = v2.x(),
			y2 = v2.y(),
			z2 = v2.z();
		
		return Vect3(
			y * z2 - z * y2,
			z * x2 - x * z2,
			x * y2 - y * x2
		);
	}
	float Vect3::length()
	{
		return std::sqrt(squaredLength());
	}
	float Vect3::squaredLength()
	{
		float 
			x = this->x(),
			y = this->y(),
			z = this->z();

		return (x * x + y * y + z * z);
	}
	void Vect3::normalize()
	{
		float l = length();

		if (l == 1.0f)
		{
			return;
		}

		if (l == 0.0f)
		{
			x(0.0f);
			y(0.0f);
			z(0.0f);

			return;
		}

		l = 1.0f / l;

		x(x() * l);
		y(y() * l);
		z(z() * l);
	}
	Vect3 Vect3::scaleAndAdd(const Vect3& a, const Vect3& b, const float& scale)
	{
		return Vect3(
			a.x() + (b.x() * scale),
			a.y() + (b.y() * scale),
			a.z() + (b.z() * scale)
		);
	}
	Vect3 Vect3::add(const Vect3& v, const Vect3& v2)
	{
		return Vect3(
			v.x() + v2.x(),
			v.y() + v2.y(),
			v.z() + v2.z()
		);
	}
	float Vect3::dot(const Vect3& v, const Vect3& v2)
	{
		float
			x = v.x(),
			y = v.y(),
			z = v.z();

		float
			x2 = v2.x(),
			y2 = v2.y(),
			z2 = v2.z();

		return (x * x2 + y * y2 + z * z2);
	}
	Vect3& Vect3::scale(float value)
	{
		this->x(x() * value);
		this->y(y() * value);
		this->z(z() * value);

		return *this;
	}
	bool Vect3::operator==(const Vect3& other) const
	{
		for (unsigned int i = 0; i < 3; ++i) {

			if (std::abs(this->_values[i] - other._values[i]) != 0.0f) {
				return false;
			}
		}
		return true;
    }
	bool Vect3::operator!=(const Vect3& v)
	{
		return !(*this == v);
	}
	bool Vect3::operator==(const Vect3& v)
	{
		return x() == v.x() && y() == v.y() && z() == v.z();
	}
	std::ostream& operator<<(std::ostream& str, const Vect3& v)
	{
		str << "Vect3(";
		str << v._values[0] << ", " << v._values[1] << ", " << v._values[2];
		str << ")";
		return str;
	}
}