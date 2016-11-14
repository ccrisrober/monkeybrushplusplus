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

#ifndef __MB_QUAT__
#define __MB_QUAT__

#include <vector>

namespace MB {
	class Quat {
	public:
		Quat(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f)
		{
			this->_values.resize(4);
			this->_values[0] = x;
			this->_values[1] = y;
			this->_values[2] = z;
			this->_values[3] = w;
		}
		void setCallback(std::function<void()> f)
		{
			this->_onChange = f;
		}
		float x() const {
			return this->_values[0];
		}
		float y() const {
			return this->_values[1];
		}
		float z() const {
			return this->_values[2];
		}
		float w() const {
			return this->_values[3];
		}
		void x(float v) {
			this->_values[0] = v;
		}
		void y(float v) {
			this->_values[1] = v;
		}
		void z(float v) {
			this->_values[2] = v;
		}
		void w(float v) {
			this->_values[3] = v;
		}
	protected:
		std::vector<float> _values;
		std::function<void()> _onChange;
	};
}

#endif /* __MB_QUAT__ */